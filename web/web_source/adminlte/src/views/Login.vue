<template>
  <div id="login-div">
    <header class="login-header">
      <a href="#" class="logo">
        <img src="/img/sysLogo.5cd27022.jpg">
        <span>MOKO TECHNOLOGY LTD.</span>
      </a>
    </header>
    <div class="login-con-div">
      <p class="title">Sign In</p>
      <label>User Name</label>
      <p><input type="text" v-model="userName"/></p>
      <label>Password</label>
      <p><input type="password" v-model="password" placeholder="Enter your password" @keyup.enter="submitSignIn"/></p>
      <div :class="[error_notice ? 'bg-danger' : '', 'error-con']">
        <span class="text-danger">{{ error_notice }}</span>
      </div>
      <button class="btn btn-primary" @click="submitSignIn">SIGN IN</button>
    </div>
  </div>
</template>
<style lang="scss">
  body {
    background-color: #ecf0f5;
  }

  #login-div {
    .login-header {
      background-color: #222d32;
      height: 60px;
      line-height: 60px;
      a {
        color: #fff;
        padding-left: 30px;
        span {
          font-size: 16px;
          margin-left: 10px;
        }
      }
    }
    .login-con-div {
      @media (max-width: 600px) {
        width: 100%;
        padding: 15px;
        height: 425px;
        top: 50%;
        margin-top: -212px;
        position: absolute;
      }
      @media (min-width: 700px) {
        top: 50%;
        left: 50%;
        margin-top: -230px;
        margin-left: -300px;
        width: 600px;
        padding: 20px;
        position: absolute;
      }
      @media (max-height: 425px) {
        position: inherit;
        margin: auto;
      }
      background-color: #fff;
      p {
        border-bottom: 1px #333 solid;
        &.title {
          font-size: 20px;
          font-weight: bold;
          padding-bottom: 10px;
        }
      }
      label {
        color: #0d6aad;
        line-height: 50px;
        font-size: 16px;
      }
      input {
        border: 0px;
        background-color: transparent;
        width: 100%;
        margin-bottom: 15px;
        &:focus {
          outline: 0px;
        }
      }
      .error-con {
        margin-top: 20px;
        height: 50px;
        margin-bottom: 20px;
        padding: 15px;
        position: relative;
        i {
          position: absolute;
          right: 0;
        }
      }
      button {
        width: 100%;
        height: 60px;
        font-size: 20px;
        font-weight: bold;
      }
    }
  }
</style>
<script>
  import {mapGetters, mapMutations} from 'vuex'
  import {RootUrl} from '../public.js'
  import {request} from '../axios'

  export default {
    name: 'login',
    data() {
      return {
        userName: 'Admin',
        password: '',
        error_notice: ''
      }
    },
    computed: {
      // 使用对象展开运算符将 getter 混入 computed 对象中
      ...mapGetters([
        'isLogined'
      ])
    },
    methods: {
      ...mapMutations([
        'loginUser'
      ]),
      submitSignIn: function () {
        this.error_notice = ''
        if (!this.userName || !this.password) {
          this.error_notice = 'The user name and password are required, please check and try again!'
          return
        }
//        this.loginUser({userName: this.userName, activeTime: 60*60*1000});
        request({
          method: 'post',
          url: (RootUrl + '/login'),
          data: {username: this.userName, password: this.password},
          headers: {'Content-Type': 'application/json'}
        }).then((response) => {
          if (response.data.state.code == 2000) {
            this.loginUser({userName: this.userName, activeTime: response.data.data.activetime});
            window.location.href = window.location.origin
          } else if (response.data.state.code == 4010 || response.data.state.code == 4020) {
            this.error_notice = 'The user name or password you entered is incorrect, please try again!'
          }
        })
      }
    }
  }
</script>