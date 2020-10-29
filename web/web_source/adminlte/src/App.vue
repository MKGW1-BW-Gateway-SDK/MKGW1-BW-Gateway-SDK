<template>
  <div id="app">
    <div class="wrapper" v-if="isLogined">
      <va-navibar></va-navibar>
      <va-slider :slideMenuItems="slideMenuItems"></va-slider>
      <va-content-wrap></va-content-wrap>
    </div>
    <template v-else>
      <router-view></router-view>
    </template>
  </div>
</template>

<script>
  import VANaviBar from './components/NaviBar'
  import VASlider from './components/Slider'
  import VAContentWrap from './components/ContentWrap'
  import slideMenuItems from './lib/slideMenuItems.js'
  import {mapGetters} from 'vuex'

  export default {
    name: 'app',
    data() {
      return {
        slideMenuItems: slideMenuItems,
      }
    },
    computed: {
      // 使用对象展开运算符将 getter 混入 computed 对象中
      ...mapGetters([
        'isLogined'
      ])
    },
    Updated: function () {
      if (!this.isLogined) {
        this.$router.push('/sign_in')
      }else if(this.$route.path == '/sign_in'){
        console.log('update to /')
        this.$router.push('/')
      }
    },
    created() {
      if (!this.isLogined) {
        this.$router.push('/sign_in')
      }else{
        console.log('create to /')
        this.$router.push('/')
      }
    },
    components: {
      'va-navibar': VANaviBar,
      'va-slider': VASlider,
      'va-content-wrap': VAContentWrap,
    }
  }
</script>

<style lang="scss">
  @import './assets/public.scss';
</style>

