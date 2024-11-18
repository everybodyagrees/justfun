import torch
from torchvision import datasets
from torch.utils.data import DataLoader
from torchvision.transforms import ToTensor
import torch.nn as nn


if torch.cuda.is_available():
    device=torch.device(type="cuda",index=0)
else:
    device=torch.device(type="cpu",index=0)

train_dataset=datasets.MNIST(
    root="data",
    train=True,
    download=True,
    transform=ToTensor(),
) #60000 thousand images
test_dataset=datasets.MNIST(
    root="data",
    train=False,
    download=True,
    transform=ToTensor(),
) #10000 thousand images

batch_size=64

train_dl=DataLoader(
    dataset=train_dataset,
    batch_size=batch_size,
    shuffle=True
)
test_dl=DataLoader(
    dataset=test_dataset,
    batch_size=batch_size, 
    shuffle=True
)

class MNISTNN(nn.Module):
    def __init__(self):
        super().__init__()
        self.relu=nn.ReLU()
        self.conv1=nn.Conv2d(in_channels=1,out_channels=8, kernel_size=(3,3), stride=1, padding=0)
        self.bn1=nn.BatchNorm2d(8)
        self.mp1=nn.MaxPool2d(kernel_size=(2,2),stride=2,padding=0)
        
        self.conv2=nn.Conv2d(in_channels=8,out_channels=16, kernel_size=(3,3), stride=1, padding=0)
        self.bn2=nn.BatchNorm2d(16)
        
        self.conv3=nn.Conv2d(in_channels=16,out_channels=32, kernel_size=(3,3), stride=1, padding=0)
        self.bn3=nn.BatchNorm2d(32)

        self.conv4=nn.Conv2d(in_channels=32,out_channels=64, kernel_size=(3,3), stride=1, padding=0)
        self.bn4=nn.BatchNorm2d(64)
               
        self.flatten=nn.Flatten()

        self.lin1=nn.Linear(in_features=3136, out_features=10)
        
            
    def forward(self,x):
        x=self.conv1(x) #64x1x28x28 -> 64x8x26x26
        x=self.bn1(x)  #64x8x26x26 -> 64x8x26x26
        x=self.relu(x) #64x8x26x26 -> 64x8x26x26
        x=self.mp1(x)  #64x8x26x26 -> 64x8x13x13
        
        x=self.conv2(x) #64x8x13x13 -> 64x16x11x11
        x=self.bn2(x) #64x16x11x11 -> 64x16x11x11
        x=self.relu(x) #64x16x11x11 -> 64x16x11x11
        
        x=self.conv3(x) #64x16x11x11 -> 64x32x9x9
        x=self.bn3(x) #64x32x9x9 -> 64x32x9x9
        x=self.relu(x) #64x32x9x9 -> 64x32x9x9

        x=self.conv4(x) #64x32x9x9 -> 64x64x7x7
        x=self.bn4(x) #64x64x7x7 -> 64x64x7x7
        x=self.relu(x) #64x64x7x7 -> 64x64x7x7

        x=self.flatten(x) #64x64x7x7 -> 64x3136

        logits=self.lin1(x) #64x3136 -> 64x10
        

        return logits
    
def train_one_epoch(dataloader, model,loss_fn, optimizer):
    model.train()
    track_loss=0
    num_correct=0
    for i, (imgs, labels) in enumerate(dataloader):
        imgs=imgs.to(device) #batch_size x num_chanels x spatial_extent
        labels=labels.to(device)
        pred=model(imgs)
                    
        loss=loss_fn(pred,labels)
        track_loss+=loss.item()
        num_correct+=(torch.argmax(pred,dim=1)==labels).type(torch.float).sum().item()
        
        running_loss=round(track_loss/(i+(imgs.shape[0]/batch_size)),2)
        running_acc=round((num_correct/((i*batch_size+imgs.shape[0])))*100,2)
        
        loss.backward()
        optimizer.step()
        optimizer.zero_grad()

        if i%100==0:
            print("Batch:", i+1, "/",len(dataloader), "Running Loss:",running_loss, "Running Accuracy:",running_acc)
            
    epoch_loss=running_loss
    epoch_acc=running_acc
    return epoch_loss, epoch_acc

def eval_one_epoch(dataloader, model,loss_fn):
    model.eval()
    track_loss=0
    num_correct=0
    with torch.no_grad():
        for i, (imgs, labels) in enumerate(dataloader):
            imgs=imgs.to(device)
            labels=labels.to(device)
            pred=model(imgs)
            loss=loss_fn(pred,labels)
            track_loss+=loss.item()
            num_correct+=(torch.argmax(pred,dim=1)==labels).type(torch.float).sum().item()
            running_loss=round(track_loss/(i+(imgs.shape[0]/batch_size)),2)
            running_acc=round((num_correct/((i*batch_size+imgs.shape[0])))*100,2)
            
            if i%100==0:
                print("Batch:", i+1, "/",len(dataloader), "Running Loss:",running_loss, "Running Accuracy:",running_acc)

    epoch_loss=running_loss 
    epoch_acc=running_acc
    return epoch_loss, epoch_acc

model=MNISTNN()
model=model.to(device)
loss_fn=nn.CrossEntropyLoss()
lr=0.001
#optimizer=torch.optim.SGD(params=model.parameters(), lr=lr)
optimizer=torch.optim.Adam(params=model.parameters(), lr=lr)
n_epochs=20

for i in range(n_epochs):
    print("Epoch No:",i+1)
    train_epoch_loss, train_epoch_acc=train_one_epoch(train_dl,model,loss_fn,optimizer)
    val_epoch_loss, val_epoch_acc=eval_one_epoch(test_dl,model,loss_fn)
    print("Training:", "Epoch Loss:", train_epoch_loss, "Epoch Accuracy:", train_epoch_acc)
    print("Inference:", "Epoch Loss:", val_epoch_loss, "Epoch Accuracy:", val_epoch_acc)
    print("--------------------------------------------------")