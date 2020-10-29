<template>
  <div id="wifi-setting-content" class="status-content-wrapper">
    <!-- Content Header (Page header) -->
    <section class="content-header">
      <ol class="breadcrumb">
        <li>
          <v-icon name="luyouqi"></v-icon>
          NETWORK
        </li>
        <li class="active">WIFI Setting</li>
      </ol>
    </section>

    <section class="content">
      <div class="content-title">WIFI Setting</div>
      <div class="content-form">
        <div class="row">
          <span class="col-md-3 text-right"><b>Gateway SSID<code>*</code>:</b></span>
          <div class="col-md-9">
            <input class="form-control" placeholder="1~32 characters" type="text" v-model="gateSsid"/>
            <code v-if="ssidError" style="line-height: 34px;">
              <i class="glyphicon glyphicon-exclamation-sign"></i>1~32 characters</code>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Hide SSID<code>*</code>:</b></span>
          <div class="col-md-9">
            <toggle-button color="#222d32" v-model="isHide" :sync="true"/>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Encrypt:</b></span>
          <div class="col-md-9">
            <select class="form-control" v-model="encrypt" style="width: 330px;">
              <option v-for="list in encryptLists" :value="list">{{ list }}</option>
            </select>
          </div>
        </div>
        <div class="row" v-if="encrypt!='NONE'">
          <span class="col-md-3 text-right"><b>New Password<code>*</code>:</b></span>
          <div class="col-md-9">
            <div class="password-input" v-if="showNewPassword">
              <input class="form-control" type="text" v-model.lazy="newPassword" :placeholder="placeholder"/>
              <a class="glyphicon glyphicon-eye-open" href="javascript:void(0)"
                 @click="showNewPassword = !showNewPassword"></a>
            </div>
            <div class="password-input" v-else>
              <input class="form-control" type="password" v-model.lazy="newPassword" :placeholder="placeholder"/>
              <a class="glyphicon glyphicon-eye-close" href="javascript:void(0)"
                 @click="showNewPassword = !showNewPassword"></a>
            </div>
            <code v-if="newPasswordError">
              <i class="glyphicon glyphicon-exclamation-sign"></i>{{ placeholder }}</code>
          </div>
        </div>
        <div class="row" v-if="encrypt!='NONE'">
          <span class="col-md-3 text-right"><b>Confirm Password<code>*</code>:</b></span>
          <div class="col-md-9">
            <div class="password-input" v-if="showConfirmPassword">
              <input class="form-control" type="text" v-model.lazy="confirmPassword"/>
              <a class="glyphicon glyphicon-eye-open" href="javascript:void(0)"
                 @click="showConfirmPassword = !showConfirmPassword"></a>
            </div>
            <div class="password-input" v-else>
              <input class="form-control" type="password" v-model.lazyl="confirmPassword"/>
              <a class="glyphicon glyphicon-eye-close" href="javascript:void(0)"
                 @click="showConfirmPassword = !showConfirmPassword"></a>
            </div>
            <code v-if="confirmPasswordError">
              <i class="glyphicon glyphicon-exclamation-sign"></i>Passwords must match.</code>
          </div>
        </div>
        <div class="row button-div">
          <div class="col-md-offset-3 col-md-9">
            <button class="btn btn-default" @click="init_data()">CANCEL</button>
            <button class="btn btn-primary" @click="submitForm()">SAVE&APPLY</button>
          </div>
        </div>
      </div>
    </section>
    <!-- /.content -->
    <need_reboot_modal></need_reboot_modal>
  </div>
</template>
<script>
  import {RootUrl, testIsOkPassword} from '../public.js'
  import {request} from '../axios'
  import NeedRebootModal from '../components/NeedReboot.vue'
  import encryptLists from '../lib/encryptLists.js'

  export default {
    name: 'wifi_setting',
    components: {
      'need_reboot_modal': NeedRebootModal,
    },
    data() {
      return {
        gateSsid: 'MKGW—BW-1900',
        encrypt: 'WPA1PSKWPA2PSK/TKIPAES',
        encryptLists: encryptLists,
        showNewPassword: true,
        showConfirmPassword: true,
        newPassword: '',
        confirmPassword: '',
        confirmPasswordError: false,
        newPasswordError: false,
        password: '',
        ssidError: false,
        d_placeholder: '8-63 characters',
        w_placeholder: '5|13 ascii characters or 10|26 hex characters',
        isHide: ''
      }
    },
    mounted: function () {
      this.init_data()
    },
    computed: {
      placeholder: function () {
        if (this.encrypt == 'WEP') {
          return this.w_placeholder
        } else {
          return this.d_placeholder
        }
      }
    },
    watch: {
      newPassword: function (val) {
        if (val) {
          if (this.encrypt == 'WEP') {
            if (!testIsOkPassword(val)) {
              this.newPasswordError = true
            } else {
              this.newPasswordError = false
            }
          } else {
            if (val.length < 8 || val.length > 63) {
              this.newPasswordError = true
            } else {
              this.newPasswordError = false
            }
          }
        } else {
          this.newPasswordError = false
        }
      },
      confirmPassword: function (val) {
        if (this.newPassword && this.newPassword != val) {
          this.confirmPasswordError = true
        } else {
          this.confirmPasswordError = false
        }
      }
    },
    methods: {
      init_data: function () {
        request({
          method: 'get',
          url: (RootUrl + '/get_wifi'),
        }).then((response) => {
          if (response.data.state.code == 2000) {
            let data = response.data.data
            this.gateSsid = data.ssid
            this.encrypt = data.encrypt
            this.password = data.password
            this.isHide = data.hidessid == '1' ? true : false
          }
        })
      },
      submitForm: function () {
        if (!this.gateSsid) {
          alert('All fields marked with * are required.')
          return
        }
        if (this.gateSsid.length < 1 || this.gateSsid.length > 32) {
          this.ssidError = true
          return
        }
        if (this.encrypt != 'NONE') {
          if (!this.newPassword) {
            alert('All fields marked with * are required.')
            return
          }
          if (this.newPassword && !this.newPasswordError && this.confirmPassword === '') {
            this.confirmPasswordError = true
          }
          if (this.newPasswordError || this.confirmPasswordError) {
            return
          }
        }
        request({
          method: 'post',
          url: (RootUrl + '/set_wifi'),
          data: {
            ssid: this.gateSsid,
            encrypt: this.encrypt,
            password: this.newPassword,
            hidessid: this.isHide ? 1 : 0,
          },
          headers: {'Content-Type': 'application/json'}
        }).then((response) => {
          if (response.data.state.code == 2000) {
            $("#needRebootModal").modal('show');
          }
        })
      }
    }
  }
</script>
