module.exports = {
  "state": {
    "code": 2000,  //返回码
    "msg": "ok"    //提示信息
  },
  "data": {
    "accessmode": "MQTT", //MQTT or HTTP
    "mqtt":{
      "interval": "10",
      "type": "TCP",
      "host": "45.77.124.18",
      "port": "1183",
      "clientid": "1183",
      "qos": "0",
      "username": "admin",
      "password": "admin",
      "pubtopic": "/pub",
      "subtopic": "/sub",
      "msgpubtopic": "/msgpub",
      "msgsubtopic": "/msgsub",
      "heartbeat": "60",
      "hbenable": 1,
    },
    "http":{
      "interval": "10",
      "username": "admin",
      "password": "admin",
      "url":"http://www.xx.sdf/ag"
    }
  }
}