import torch
import torch.nn as nn
from torch import optim
from torch.optim import lr_scheduler
from torch.utils.data import DataLoader
from torchvision import datasets, transforms, models
import os
from matplotlib import pyplot as plt
import time
import copy

#cpu or gpu
device=("cuda" if torch.cuda.is_available() else "cpu")
print("Device:", device)


#setting root directory
image_dir="ants_and_bees"
batch_size=4

#preparing Transform
train_transform=transforms.Compose([transforms.Resize(size=(224,224)),transforms.RandomHorizontalFlip(),transforms.ToTensor()])
val_transform=transforms.Compose([transforms.Resize((224,224)),transforms.ToTensor()])

#preparing Transform
Train_Dataset=datasets.ImageFolder(root=os.path.join(image_dir,"train"),transform=train_transform)
Val_Dataset=datasets.ImageFolder(root=os.path.join(image_dir,"val"), transform=val_transform)

# Attributes:
# classes (list): List of the class names sorted alphabetically.
# class_to_idx (dict): Dict with items (class_name, class_index).
# imgs (list): List of (image path (from the current
# directory to the filename), class_index) tuples

print(type(Train_Dataset))
#<class 'torchvision.datasets.folder.ImageFolder'>

print(type(Train_Dataset[0]))
#<class 'tuple'>

#Checking if the DataSet is correctly prepared

print(Train_Dataset[0][0].shape)
#shape of zeroth image, torch.Size([3, 224, 224]) 

print(Train_Dataset[0][1])
#label of zeroth image, 0

class_list=Train_Dataset.classes
print(class_list)
#['ants', 'bees']

classes_to_ids=Train_Dataset.class_to_idx
print(classes_to_ids)
#{'ants': 0, 'bees': 1}

#Wrapping DataLoadeer
Train_DataLoader=DataLoader(Train_Dataset,batch_size=batch_size, shuffle=True)
Val_DataLoader=DataLoader(Val_Dataset,batch_size=batch_size, shuffle=True)

#Taking a glimpse at the data
X,y=next(iter(Train_DataLoader))
plt.subplot(2,2,1)
plt.imshow(torch.moveaxis(X[0],0,2)) #channel first to last
plt.title(class_list[y[0]])
plt.subplot(2,2,2)
plt.imshow(torch.moveaxis(X[1],0,2))
plt.title(class_list[y[1]])
plt.subplots_adjust(hspace=0.5)
plt.subplot(2,2,3)
plt.imshow(torch.moveaxis(X[2],0,2))
plt.title(class_list[y[2]])
plt.subplot(2,2,4)
plt.imshow(torch.moveaxis(X[3],0,2))
plt.title(class_list[y[3]])
plt.suptitle("A Batch of Four")
plt.show()

class FixedNN(nn.Module):
    def __init__(self):
        super().__init__()
        #pretrained model
        self.pretraiend=models.resnet18(weights=models.ResNet18_Weights.DEFAULT)
        #freeze parameters
        for param in self.pretraiend.parameters():
            param.requires_grad=False
        #code size
        num_features=self.pretraiend.fc.in_features
        #changing fc
        self.pretraiend.fc=nn.Linear(num_features,len(class_list))

    def forward(self,X):
        logits=self.pretraiend(X)
        return logits

fixed_model=FixedNN().to(device)
loss=nn.CrossEntropyLoss()
opt=optim.Adam(params=fixed_model.pretraiend.fc.parameters(),lr=0.001)
lr_s=lr_scheduler.StepLR(optimizer=opt,step_size=10,gamma=0.1)

best_epoch=1
best_acc=0

def train(model,loss,opt,lr_s,n_epochs=2):
    global best_epoch,best_acc
    start=time.time()
    best_acc=0.0
    best_model_wt=copy.deepcopy(model.state_dict())
    for e in range(n_epochs):
        print("Epoch", e+1, "/", n_epochs, ":")
        running_loss=0.0
        running_correct=0
        running_loss_val=0.0
        running_correct_val=0
        model.train()
        #batch=1
        #print("Batch:", end='')
        Train_DataLoader=iter(Train_DataLoader)
        for X,y in Train_DataLoader:
            #print(batch, end=',')
            #batch=batch+1
            X=X.to(device)
            y=y.to(device)
            opt.zero_grad()
            
            with torch.set_grad_enabled(True):
                logits=model(X)
                _,preds=torch.max(logits,dim=1)
                l=loss(logits,y)
                l.backward()
                opt.step()
            running_loss+=l*X.size(0)
            running_correct+=torch.sum(preds==y.detach())
        lr_s.step()
        #print(running_correct/(batch*batch_size), " ")
        
        epoch_loss_train=running_loss/len(Train_Dataset)
        epoch_correct_train=running_correct.double()/len(Train_Dataset)
        
        
        #val_batch=1
        model.eval()

        for X_val,y_val in Val_DataLoader:
            #print(val_batch, end=',')
            #val_batch+=1
            X_val=X_val.to(device)
            y_val=y_val.to(device)
            opt.zero_grad()
            
            with torch.set_grad_enabled(False):
                logits=model(X_val)
                _,preds=torch.max(logits,dim=1)
                l=loss(logits,y_val)
            running_loss_val+=l*X_val.size(0)
            running_correct_val+=torch.sum(preds==y_val.detach())
            #print(running_correct_val/(val_batch*batch_size), " ")
            
        epoch_loss_val=running_loss_val/len(Val_Dataset)
        epoch_correct_val=running_correct_val.double()/len(Val_Dataset)

        print("Training Loss:", epoch_loss_train, "Training Accuracy:", epoch_correct_train, "Validation Loss:", epoch_loss_val, "Validation Accuracy:", epoch_correct_val)

        if epoch_correct_val > best_acc:
            best_epoch=e+1
            best_acc=epoch_correct_val
            best_model_wt=copy.deepcopy(model.state_dict())
    
    time_elapsed=time.time()-start
    print("Training Time is",time_elapsed, "Seconds")
    model.load_state_dict(best_model_wt)
    return model

trained_model=train(fixed_model,loss,opt,lr_s,2)
torch.save(trained_model,"tl_fixed_" + str(best_epoch) + "_ValAcc_" + str(round(best_acc.item(),4)) + ".pth")