import Vue from 'vue'
import Vuex from 'vuex'
import * as state from './states'
import * as getters from './getters'
import * as mutations from './mutations'

Vue.use(Vuex)

export default new Vuex.Store({
  state,
  getters,
  mutations,
  strict: process.env.NODE_ENV !== 'production'
})