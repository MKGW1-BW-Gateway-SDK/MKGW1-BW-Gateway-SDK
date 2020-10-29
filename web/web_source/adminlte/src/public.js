export let hoursParams = getTimeArray(24);
export let minutesParams = getTimeArray(60);
export let userName = 'admin';
export let password = '123456';
let host = window.location.origin
export let  RootUrl = host+'/goform';
export let  RootSetUrl = host+'/cgi-bin';

/*
 * 检测对象是否是空对象(不包含任何可读属性)。
 * 方法既检测对象本身的属性，也检测从原型继承的属性(因此没有使hasOwnProperty)。
 */
export function isNotEmpty(obj, ignore) {
  if (!ignore) {
    ignore = []
  }
  {
    for (var name in obj) {
      if (obj[name] && ignore.indexOf(name) == -1) {
        return true;
      }
    }
    return false;
  }
}

function getTimeArray(length) {
  let hoursParams = [];
  let i = 0;
  for(i = 0; i<=length; i++){
    if(i < 10){
      hoursParams.push('0'+i)
    }else{
      hoursParams.push(i)
    }
  }
  return hoursParams
}

function testIsAscii(str)
{
  for( var i = 0; i < str.length; i++)
  {
    var chr = str.charCodeAt(i);
    if( chr < 0 || chr > 255 )
    {
      return false;
    }
  }
  return true;
}

export  function testIsOkPassword(str){
  if(str.length == 5 || str.length == 13){
    return testIsAscii(str)
  }else if(str.length == 10 || str.length == 26){
    var reg=/^[0-9a-fA-F]+$/
    return reg.exec(str) != null
  }else{
    return false
  }
}


Date.prototype.Format = function (fmt) { //author: meizz
  var o = {
    "M+": this.getMonth() + 1, //月份
    "d+": this.getDate(), //日
    "h+": this.getHours(), //小时
    "m+": this.getMinutes(), //分
    "s+": this.getSeconds(), //秒
    "q+": Math.floor((this.getMonth() + 3) / 3), //季度
    "S": this.getMilliseconds() //毫秒
  };
  if (/(y+)/.test(fmt)) fmt = fmt.replace(RegExp.$1, (this.getFullYear() + "").substr(4 - RegExp.$1.length));
  for (var k in o)
    if (new RegExp("(" + k + ")").test(fmt)) fmt = fmt.replace(RegExp.$1, (RegExp.$1.length == 1) ? (o[k]) : (("00" + o[k]).substr(("" + o[k]).length)));
  return fmt;
}

export function testIsIp(str){
  var re = /^((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})(\.((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})){3}$/
  return re.test(str)
}

export function testIshost(str) {
  var re = /^(?=^.{3,255}$)[a-zA-Z0-9][-a-zA-Z0-9]{0,62}(\.[a-zA-Z0-9][-a-zA-Z0-9]{0,62})+$/
  return re.test(str)
}

export function testIsUrl(str) {
  var strRegex = '^((https|http|ftp|rtsp|mms)?://)'
    + '?(([0-9a-z_!~*\'().&=+$%-]+: )?[0-9a-z_!~*\'().&=+$%-]+@)?' //ftp的user@
    + '(([0-9]{1,3}.){3}[0-9]{1,3}' // IP形式的URL- 199.194.52.184
    + '|' // 允许IP和DOMAIN（域名）
    + '([0-9a-z_!~*\'()-]+.)*' // 域名- www.
    + '([0-9a-z][0-9a-z-]{0,61})?[0-9a-z].' // 二级域名
    + '[a-z]{2,6})' // first level domain- .com or .museum
    + '(:[0-9]{1,4})?' // 端口- :80
    + '((/?)|' // a slash isn't required if there is no file name
    + '(/[0-9a-z_!~*\'().;?:@&=+$,%#-]+)+/?)$';
  var re=new RegExp(strRegex);
  return re.test(str)
}