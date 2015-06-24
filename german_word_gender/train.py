# coding: utf-8
from sklearn import cross_validation
from sklearn import ensemble, tree
import numpy
import random

data = []
target = []
indices = {}
for i in range(ord('a'), ord('z')+1):
	indices[unichr(i)] = i - ord('a')
for i in range(ord('A'), ord('Z')+1):
	indices[unichr(i)] = i - ord('A')
indices[u'ä'] = indices[u'Ä'] = 26
indices[u'ö'] = indices[u'Ö'] = 27
indices[u'ü'] = indices[u'Ü'] = 28
indices[u'ß'] = 29
for line in open('data').readlines():
	gender, word = line.strip().decode('utf-8').split()
	if filter(lambda x: ord(x) in range(ord('A'), ord('Z')+1) or x in [u'Ä', u'Ö', u'Ü'], word[1:]):
		continue
	this_data = [0 for i in range(0, 720)]
	for i in range(0, len(word)):
		this_data[(len(word)-i-1) * 30 + indices[word[i]]] = 1
	this_target = 0 if gender == u'MAS' else (1 if gender == u'FEM' else 2)
	data.append(this_data)
	target.append(this_target)
data = numpy.array(data)
target = numpy.array(target)

data_train, data_test, target_train, target_test = cross_validation.train_test_split(data, target, test_size=0.4)
model = ensemble.AdaBoostClassifier(base_estimator=tree.DecisionTreeClassifier(max_depth=6), n_estimators=400)
model.fit(data_train, target_train)
model_predict = model.predict(data_test)
correct = model_predict == target_test
print numpy.mean(correct)
