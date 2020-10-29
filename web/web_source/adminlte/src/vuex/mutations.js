// import * as state from './states'

export const loginUser = (state, userInfo) => {
  state.currentUser.name = userInfo.userName
  state.currentUser.dueTime = Date.now() + userInfo.activeTime
  try {
    localStorage.setItem('currentUser', JSON.stringify({name: state.currentUser.name, dueTime: state.currentUser.dueTime}))
  } catch (e) {
    alert('您当前处于无痕浏览，进一步操作,请更改浏览器设置')
  }
}

export const signOut = (state) => {
  state.currentUser.name = null
  state.currentUser.dueTime = null
  window.localStorage.removeItem('currentUser')
}
