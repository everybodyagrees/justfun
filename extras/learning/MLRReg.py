import numpy as np
from sklearn import datasets, metrics
from sklearn.preprocessing import StandardScaler
#from sklearn.datasets import fetch_california_housing
from numpy.linalg import inv, LinAlgError
from sklearn.model_selection import train_test_split
from sklearn.linear_model import Lasso, Ridge
from sklearn.linear_model import SGDRegressor

(Xtemp,y)=datasets.fetch_california_housing(return_X_y=True) 
#20640 instances, 8 numeric features + target is  the median house value for California districts,
#expressed in hundreds of thousands of dollars, no missing data 

#adding a dummy variable
X=np.ones((Xtemp.shape[0], Xtemp.shape[1]+1))
#print(type(X), X.shape)
X[:,1:]=Xtemp

#train-test split
X_train,X_test,y_train,y_test=train_test_split(X,y,test_size=0.2,random_state=42)
print("Data:")
print("X:", X.shape, "y:", y.shape, "X_train:", X_train.shape, "X_test:", X_test.shape, "y_train:", y_train.shape, "y_test:", y_test.shape)

#scale data
ss=StandardScaler()
ss.fit(X_train[:,1:])
X_train[:,1:]=ss.transform(X_train[:,1:])
X_test[:,1:]=ss.transform(X_test[:,1:])

#Linear Regression using Regularized Batch Gradient Descent using numpy
print("#Linear Regression using Regularized Batch Gradient Descent using numpy#")
niterations=1000
m=X_train.shape[0]
n=X_train.shape[1]
lr=0.01
lambda1=0.005
alpha=0.005
#theta=np.random.uniform(0,1,size=(n))
theta=np.zeros(n)
update=np.zeros(n)
for i in range(niterations):
    ypred=np.dot(X_train,theta)
    error=ypred - y_train; #be mindful of this order in difference
    for j in range(n):
        update[j]=np.sum(error*((X_train.T)[j]))
    theta[0]=theta[0]-lr*(1/m)*update[0]
    theta[1:]=theta[1:]*(1-(lr*lambda1/m))-(lr)*(1/m)*update[1:]
print("Thetas:", theta)
print("Thetas Shape:", theta.shape)
pred=np.dot(X_test,theta);
print("MAE:", metrics.mean_absolute_error(y_test,pred))
print("MSE:", metrics.mean_squared_error(y_test,pred))


#Linear Regression using Regularized Normal Equation Method (Ridge) using numpy
print("#Linear Regression using Regularized Normal Equation Method (Ridge) using numpy#")
theta=np.zeros(X_train.shape[1])
add_mat=np.eye(n,n)
add_mat[0,0]=0

#np.dot(X_train.T,X_train)+lambda1*add_mat is certainely invertible
XTXi=inv(np.dot(X_train.T,X_train)+lambda1*add_mat)

XTy=np.dot(X_train.T,y_train)
theta=np.dot(XTXi,XTy)
print("Thetas:", theta)
print("Thetas Shape:", theta.shape)
predictions=np.dot(theta,X_test.T)
print("MAE:", metrics.mean_absolute_error(y_true=y_test,y_pred=predictions))
print("MSE:", metrics.mean_squared_error(y_true=y_test,y_pred=predictions))


####Now using sklearn##########################################

#Please note, it automatically adds dummy variable
#so, removing dummy variable
X_train=X_train[:,1:]
X_test=X_test[:,1:]



#Linear Regression using Regularized Normal Equation Method (Lasso) using sklearn
print("#Linear Regression using Normal Equation Method (Lasso) using sklearn")
lr=Lasso(alpha=alpha)
lr.fit(X_train,y_train)
print("Theta1...Thetan:", lr.coef_)
print("Intercept:",lr.intercept_)
predictions=lr.predict(X_test)
print("MAE:", metrics.mean_absolute_error(y_true=y_test,y_pred=predictions))
print("MSE:", metrics.mean_squared_error(y_true=y_test,y_pred=predictions))

#Linear Regression using Regularized Normal Equation Method (Ridge) using sklearn
print("#Linear Regression using Normal Equation Method (Ridge) using sklearn")
lr=Ridge(alpha=alpha)
lr.fit(X_train,y_train)
print("Theta1...Thetan:", lr.coef_)
print("Intercept:",lr.intercept_)
predictions=lr.predict(X_test)
print("MAE:", metrics.mean_absolute_error(y_true=y_test,y_pred=predictions))
print("MSE:", metrics.mean_squared_error(y_true=y_test,y_pred=predictions))

#Linear Regression using Regularized Stochastic Gradient Descent using sklearn
print("#Linear Regression using Regularized Stochastic Gradient Descent using sklearn")
sgd=SGDRegressor(eta0=0.01, max_iter=1000, alpha=alpha)
sgd.fit(X_train,y_train)
print("Theta1...Thetan:", sgd.coef_)
print("Intercept:",sgd.intercept_)
predictions=sgd.predict(X_test)
print("MAE:", metrics.mean_absolute_error(y_true=y_test,y_pred=predictions))
print("MSE:", metrics.mean_squared_error(y_true=y_test,y_pred=predictions))