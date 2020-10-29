import axios from 'axios'
import store from './vuex/store'
import Qs from 'qs';

axios.defaults.retry = 1000;
axios.defaults.retryDelay = 1000;


//请求返回拦截，把数据返回到页面之前做些什么...
axios.interceptors.response.use((response) => {
    //特殊错误处理，状态为4040时为超时
    if (response.data.state.code === 4040) {
      console.log('统一的超时处理')
      store.commit('signOut')
      window.location.href = window.location.origin
      //请求成功
    } else {
      //将我们请求到的信息返回页面中请求的逻辑
      return response;
    }
  },
  function axiosRetryInterceptor(err) {
    var config = err.config;
    if(!config || !config.retry) return Promise.reject(err);
    config.__retryCount = config.__retryCount || 0;
    if(config.__retryCount >= config.retry || (err.message.indexOf('timeout')==-1 && err.message.indexOf('Network Error')==-1) ){
      return Promise.reject(err);
    }
    config.__retryCount += 1;
    var backoff = new Promise(function(resolve){
      setTimeout(function(){
        resolve();
      }, config.retryDelay || 1000);
    });
    return backoff.then(function(){
      return axios(config);
    })
  })

// axios中的请求转换器， 允许在向服务器发送前，修改数据，只能用在'put','post'和'patch'这几个请求方法
axios.defaults.transformRequest = [function (data, config) {
  // 如果没有额外设置请求头的时候，直接返回一个用&连接的序列化结果
  if (!config['Content-Type']) return Qs.stringify(data);
  switch (config['Content-Type'].toLowerCase()) {
    case 'application/json':
      return JSON.stringify(data);
    case 'multipart/form-data':
      return data;
    default:
      return Qs.stringify(data);
  }
}]

export const request = (config) => {
  return axios(config)
}