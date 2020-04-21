import urllib2  

output = '<?xml version="1.0" encoding="UTF-8"?>\n<kml xmlns="http://earth.google.com/kml/2.2">\n<Document>\n\t<name>youbike</name>\n'

content = urllib2.urlopen('http://its.taipei.gov.tw/atis_index/aspx/Youbike.aspx?Mode=1').read()
lines = content.split('|')

for oneLine in lines:
    tokens = oneLine.split('_')

    if len(tokens) == 12:
        output += '\t<Placemark>\n\t\t<name>'
        output += tokens[1]
        output += '</name>\n\t\t<description><![CDATA['
        output += tokens[7]
        output += ']]></description>\n\t\t<Point>\n\t\t\t<coordinates>'
        output += (tokens[6] + ',' + tokens[5]) 
        output += '</coordinates>\n\t\t</Point>\n\t</Placemark>\n'

output += '</Document>\n</kml>'

f = open('youbike.kml', 'w')
f.write(output)
f.close()