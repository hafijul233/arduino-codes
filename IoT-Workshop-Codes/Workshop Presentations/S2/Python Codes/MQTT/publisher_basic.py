import paho.mqtt.client as mqtt #import the client1
#broker_address="192.168.1.101" 
broker_address="iot.eclipse.org" #use external broker
client = mqtt.Client("P1") #create new instance
client.connect(broker_address) #connect to broker
client.publish("house/main-light","ON")#publish