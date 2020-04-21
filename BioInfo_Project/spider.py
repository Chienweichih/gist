import requests
from bs4 import BeautifulSoup
import HTMLParser
import time
from random import randint
import sys
from IPython.display import clear_output

links = []
pid = []

input_list = open('pmid_list.txt','r')

pid = input_list.read().splitlines()
links = ["http://www.ncbi.nlm.nih.gov/pubmed/" + line for line in pid]

input_list.close()

for i in range(len(links)):

    res = requests.get(links[i])
    soup = BeautifulSoup(res.text.encode("utf-8"))
	
    try:
        abstr = soup.find('div',{'class':'abstr'})
        div = abstr.find('div',{'class': ''})
        p = div.find('p')
        AbstractText = p.abstracttext.string.strip()
    except Exception as e:
        AbstractText = ""
        
    output_list = open(pid[i] + '.txt','w')
    output_list.write(AbstractText.encode('utf-8'))
    output_list.close()
    
    clear_output()
    print (i)
    sys.stdout.flush()
