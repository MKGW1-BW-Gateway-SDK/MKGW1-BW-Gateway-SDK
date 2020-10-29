<template>
  <header class="main-header">
    <!-- Logo -->
    <div class="logo">
      <!-- mini logo for sidebar mini 50x50 pixels -->
      <div class="logo-mini">
        <img src="../assets/img/sysLogo.jpg"/>
      </div>
      <!-- logo for regular state and mobile devices -->
      <div class="logo-lg">
        <img src="../assets/img/sysLogo.jpg"/>
        <div>
          <p>MOKO IOT</p>
          <p>GATEWAY</p>
        </div>
      </div>
    </div>

    <!-- Header Navbar: style can be found in header.less -->
    <nav class="navbar navbar-static-top">
      <!-- Sidebar toggle button-->
      <a href="#" class="sidebar-toggle" data-toggle="push-menu" role="button">
        <span class="sr-only">Toggle navigation</span>
      </a>
      <!-- Navbar Right Menu -->
      <div class="navbar-custom-menu">
        <ul class="nav navbar-nav">
          <!-- Messages: style can be found in dropdown.less-->
          <!--<li class="dropdown">-->
            <!--<a href="#" class="dropdown-toggle" data-toggle="dropdown">-->
              <!--<v-icon name="language"></v-icon>-->
              <!--<span class="hidden-xs">Language</span>-->
            <!--</a>-->
            <!--<ul class="dropdown-menu">-->
              <!--<li><a href="#">English</a></li>-->
              <!--<li><a href="#">中文</a></li>-->
            <!--</ul>-->
          <!--</li>-->
          <!-- User Account: style can be found in dropdown.less -->
          <!--<li class="dropdown">-->
          <!--<a href="#">-->
          <!--<v-icon name="user"></v-icon>-->
          <!--<span class="hidden-xs">{{ currentUser.name }}</span>-->
          <!--</a>-->
          <!--</li>-->
          <li class="dropdown">
            <a href="javascript:void(0)" @click="submitSignOut()">
              <v-icon name="log-out"></v-icon>
              <span class="hidden-xs">Sign out</span>
            </a>
          </li>
        </ul>
      </div>
    </nav>
  </header>
</template>

<script>
  import {mapState, mapMutations} from 'vuex'
  import {RootUrl} from '../public.js'
  import {request} from '../axios'

  export default {
    name: 'va-navibar',
    computed: {
      ...mapState([
        'currentUser'
      ])
    },
    methods: {
      ...mapMutations([
        'signOut'
      ]),
      submitSignOut: function () {
        request({
          method: 'get',
          url: (RootUrl + '/logout'),
        }).then((response) => {
          if (response.data.state.code == 2000) {
            this.signOut()
            window.location.href = window.location.origin
          }
        })
      }
    }
  }

</script>
