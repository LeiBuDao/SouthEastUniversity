#%%
import os
import random
import pynamesgenerator
#%%
 
# %%
def createRecord(i):
  def generateSex():
    if random.randint(0, 1) == 0:
      return '"m"'
    else:
      return '"f"'
  record = ''
  record += str(i)
  record += '\t'
  record += '"'
  record += pynamesgenerator.gen_two_words()
  record += '"'
  record += '\t'
  record += generateSex()
  record += '\t'
  record += str(random.randint(18, 30))
  record += '\t'
  record += str(random.randint(1, 5))
  record += '\t'
  record += str(random.randint(1, 40) / 10.00)
  record += '\n'
  return record

print(createRecord(105))
# %%
file = open('./' + 'new' + '.txt','w')
for i in range(105, 5001):
  file.writelines(createRecord(i))
file.close()


# %%
