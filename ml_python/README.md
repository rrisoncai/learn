# system setup
```python
# crete workspace
export ML_PATH="$HOME/ml"
mkdir -p $ML_PATH
pip3 --version
pip3 install --upgrade pip
pip3 install --user --upgrdade virtualenv

# setup virtualenv
cd $ML_PATH
virtualenv env

# activate existing virtualenv
cd $ML_PATH
source env/bin/activate
```
# repository for machine learning in python
- perceptron
- knn
- logistic regression
