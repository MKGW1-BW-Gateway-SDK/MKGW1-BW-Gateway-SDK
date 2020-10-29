module.exports = [
  {
    type: 'item',
    icon: '__font_icon__ v-icon v-icon-fazhuangtai',
    name: 'STATUS',
    router: {
      name: 'status'
    }
  },
  {
    type: 'tree',
    icon: '__font_icon__ v-icon v-icon-luyouqi',
    name: 'NETWORK',
    items: [
      {
        type: 'item',
        icon: '',
        name: 'Internet Setting',
        router: {
          name: 'internet_setting'
        }
      },
      {
        type: 'item',
        icon: '',
        name: 'WIFI Setting',
        router: {
          name: 'wifi_setting'
        }
      },
      {
        type: 'item',
        icon: '',
        name: 'LAN Setting',
        router: {
          name: 'lan_setting'
        }
      }
    ]
  },
  {
    type: 'tree',
    icon: '__font_icon__ v-icon v-icon-yunzhujiyunfuwuqijiagou',
    name: 'FUNCTION',
    items: [
      {
        type: 'item',
        icon: '',
        name: 'Server Access',
        router: {
          name: 'server_access'
        }
      },
      {
        type: 'item',
        icon: '',
        name: 'BLE Option',
        router: {
          name: 'ble_option'
        }
      }
    ]
  },
  {
    type: 'tree',
    icon: '__font_icon__ v-icon v-icon-SystemSetting',
    name: 'SYSTEM',
    items: [
      {
        type: 'item',
        icon: '',
        name: 'Device Setting',
        router: {
          name: 'system'
        }
      },
      {
        type: 'item',
        icon: '',
        name: 'Backup&Upgrade',
        router: {
          name: 'backup_upgrade'
        }
      }
    ]
  }
]
