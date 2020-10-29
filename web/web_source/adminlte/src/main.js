import 'va/lib/css'
import 'va/lib/script'
import VueIconfont from 'vue-iconfont'
import './assets/iconfont/iconfont.css'
import './assets/iconfont/iconfont'
import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './vuex/store'
import ToggleButton from 'vue-js-toggle-button'

Vue.use(ToggleButton)
Vue.use(VueIconfont,[
  // 定义 v-icon 组件以使用 font-class 图标
  {
    tag: 'v-icon',
    prefix: 'v-icon',
    type: 'font'
  },

  // 定义 v-svg-icon 组件以使用 SVG 图标
  {
    tag: 'v-svg-icon',
    prefix: 'v-icon',
    type: 'svg'
  }
])
Vue.config.productionTip = false

new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')

