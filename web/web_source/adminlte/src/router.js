import Vue from 'vue'
import Router from 'vue-router'
import Status from './views/Status.vue'
import InternetSetting from './views/InternetSetting.vue'
import WifiSetting from './views/WifiSetting.vue'
import LanSetting from './views/LanSetting.vue'
import BackupUpgrade from './views/BackupUpgrade.vue'
import ServerAccess from './views/ServerAccess.vue'
import BLEOption from './views/BLEOption.vue'
import System from './views/System.vue'
import Login from './views/Login.vue'

Vue.use(Router)

const  router = new Router({
  mode: 'history',
  base: process.env.BASE_URL,
  routes: [
    {
      path: '/',
      name: 'status',
      component: Status,
    },
    {
      path: '/internet_setting',
      name: 'internet_setting',
      component: InternetSetting,
    },
    {
      path: '/wifi_setting',
      name: 'wifi_setting',
      component: WifiSetting,
    },
    {
      path: '/lan_setting',
      name: 'lan_setting',
      component: LanSetting,
    },
    {
      path: '/backup_upgrade',
      name: 'backup_upgrade',
      component: BackupUpgrade,
    },
    {
      path: '/server_access',
      name: 'server_access',
      component: ServerAccess,
    },
    {
      path: '/ble_option',
      name: 'ble_option',
      component: BLEOption,
    },
    {
      path: '/system',
      name: 'system',
      component: System,
    },
    {
      path: '/sign_in',
      name: 'login',
      component: Login,
    }
  ]
})

// router.beforeEach((to,from,next) => {
//   console.log(to)
//   console.log(from)
//   next(vm=>{
//     vm.$router.replace({path: to.path, query: {t: Date.now()}})
//   })
// })

export default router