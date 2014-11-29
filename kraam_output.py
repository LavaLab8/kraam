import json 
import time as dt
import dateutil.parser as dparser
def parseCommaList(str):
	listODays = []
        day = {"Monday":"Monday", "Tuesday":"Tuesday","Wednesday":"Wednesday", "Thursday":"Thursday", "Friday":"Friday", "Mon":"Monday", "Tue":"Tuesday",
	       "Wed":"Wednesday", "Thu":"Thursday", "Fri":"Friday", "MWF":["Monday","Wednesday", "Friday"], "MW":["Monday","Wednesday"], "TTh": ["Tuesday","Thursday"],
		 "MTuWThF":["Monday", "Tuesday", "Wednesday", "Thursday", "Friday"] }
	unInterpretedList = str.split(',')
	for i in unInterpretedList:
		if len(i) > 1:
		 	if i[0] == " ":
				listODays.append(day[i[1:]])
			elif i[-1] == " ":
				listODays.append(day[i[:-2]])
			
			elif i != "TBA" and type(day[i]) == type([]):
				for j in day[i]:
					listODays.append(j)
			else:
				if i != "TBA" and i != "":	
					listODays.append(day[i])
	return listODays
				
# interpretClassTime("7:00-8:50pm") -> {"start": 19:00, "end": 20:50}

def convertToMilitaryTime(str):
	listOtimes = []
	militaryTime = None
	returnArray = []
#	print ">>>>>>>>>>>",str
	if str == "TBA" or str == "":
		return {"start": "N/A", "end": "N/A"}
	unInterpretedList = str.split('-')

	#check am to pm
	try:
		first2Digits = int(unInterpretedList[0].split(':')[0])
		if first2Digits < 12 and first2Digits >= 9:
			unInterpretedList[0] = unInterpretedList[0] + "am"
		elif first2Digits >= 1 and first2Digits <= 6:
			unInterpretedList[0] = unInterpretedList[0] + "pm"
		else:
			amOrPm = str[-2:]
			unInterpretedList[0] = unInterpretedList[0] + amOrPm
	except:
		pass
	#	print convertToMilitaryTime(class["Time"])
	#converts to date
	for i in unInterpretedList:
		if i[-2:] == "am" or i[:2] == "12":
			newTime = i[:-2]
			preTime = newTime.replace(":", "")
			militaryTime = int(preTime)
		elif i[-2:] == "pm":
			newTime = i[:-2]
			preTime = newTime.replace(":", "")
			militaryTime = int(preTime)
			militaryTime += 1200
		returnArray.append(militaryTime)
	for i in unInterpretedList:
		listOtimes.append(dparser.parser(i))
	return {"start": returnArray[0] ,"end": returnArray[1] }

with open ("lava.json") as json_file:
	json_data = json.load(json_file)
	#print json_data
day = raw_input("Enter a day: ")
time = raw_input("Enter a time with am or pm: ")
days = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday"]
if day not in days:
	day = raw_input("Enter a day: ")
	time = raw_input("Enter a time: ")
if time[-2:] == "am" or time[-2:] == "AM" or time[:2] == "12":
	newTime = time[:-2]
	preTime = newTime.replace(":", "")
	finalTime = int(preTime)
elif time[-2:] == "pm" or time[-2:] == "PM":
	newTime = time[:-2]
	preTime = newTime.replace(":", "")
	finalTime = int(preTime)
	finalTime += 1200
for i in json_data:
	if finalTime >= convertToMilitaryTime(i["Time"])["start"] and finalTime <= convertToMilitaryTime(i["Time"])["end"]:
	#	print i["Course Title"]
		print i["Room"]
		
#for obj in json_data:
#	if(obj["Days"] = 
