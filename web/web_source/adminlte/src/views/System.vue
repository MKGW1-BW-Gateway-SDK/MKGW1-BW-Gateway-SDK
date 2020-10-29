<template>
  <div id="ble-option-content" class="status-content-wrapper">
    <!-- Content Header (Page header) -->
    <section class="content-header">
      <ol class="breadcrumb">
        <li>
          <v-icon name="SystemSetting"></v-icon>
          SYSTEM
        </li>
        <li class="active">Device Setting</li>
      </ol>
    </section>

    <section class="content">
      <div class="content-title">Admin Password</div>
      <div class="content-form">
        <div class="row">
          <span class="col-md-3 text-right"><b>User Name:</b></span>
          <div class="col-md-9">
            <span>Admin</span>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Old Password:</b></span>
          <div class="col-md-9">
            <div class="password-input" v-if="showOldPassword">
              <input class="form-control" type="text" v-model.lazy="oldPassword" maxlength="64" minlength="1"
                     placeholder="1-64 characters"/>
              <a class="glyphicon glyphicon-eye-open" href="javascript:void(0)"
                 @click="showOldPassword = !showOldPassword"></a>
            </div>
            <div class="password-input" v-else>
              <input class="form-control" type="password" v-model.lazy="oldPassword" maxlength="64" minlength="1"
                     placeholder="1-64 characters"/>
              <a class="glyphicon glyphicon-eye-close" href="javascript:void(0)"
                 @click="showOldPassword = !showOldPassword"></a>
            </div>
            <code v-if="oldPasswordError">
              <i class="glyphicon glyphicon-exclamation-sign"></i>Incorrect password.</code>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>New Password:</b></span>
          <div class="col-md-9">
            <div class="password-input" v-if="showNewPassword">
              <input class="form-control" type="text" v-model.lazy="newPassword" maxlength="64" minlength="1"
                     placeholder="1-64 characters"/>
              <a class="glyphicon glyphicon-eye-open" href="javascript:void(0)"
                 @click="showNewPassword = !showNewPassword"></a>
            </div>
            <div class="password-input" v-else>
              <input class="form-control" type="password" v-model.lazy="newPassword" maxlength="64" minlength="1"
                     placeholder="1-64 characters"/>
              <a class="glyphicon glyphicon-eye-close" href="javascript:void(0)"
                 @click="showNewPassword = !showNewPassword"></a>
            </div>
            <code v-if="newPasswordError">
              <i class="glyphicon glyphicon-exclamation-sign"></i>must input and 1-64 characters.</code>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Confirm Password:</b></span>
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
            <button class="btn btn-default" @click="init_data('adminPassword')">CANCEL</button>
            <button class="btn btn-primary" @click="submitAdminPasswordForm()">SAVE&APPLY</button>
          </div>
        </div>
      </div>

      <div class="content-title">Time Configuration</div>
      <div class="content-form">
        <div class="row">
          <span class="col-md-3 text-right"><b>Local Time:</b></span>
          <div class="col-md-9">
            <span>{{ localTime }}</span>
            <button style="margin-left: 10px;" class="btn btn-default" @click="setLocalTime()">Sync With Browser
            </button>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Time Zone:</b></span>
          <div class="col-md-9">
            <select class="form-control" v-model="timeZoneValue">
              <option v-for="tzv in timeZoneLists" :value="tzv[0]+','+tzv[1]">{{ tzv[0] }}</option>
            </select>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Set Automatically:</b></span>
          <div class="col-md-9">
            <input type="checkbox" v-model="ntpEnable"/>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>NTP Server Candidates<code>*</code>:</b></span>
          <div class="col-md-9">
            <div v-for="ntp, i in ntpServer" :class="[i==(ntpServer.length-1) ? 'inlineBlock' : 'nextP']">
              <input class="form-control" type="text" v-model="ntpServer[i]"/>
              <a class="add_a" @click="removeOneServer(i)" href="javascript:void(0)">-</a>
            </div>
            <a class="add_a" v-if="ntpServer.length < 16" @click="addOneServer()" href="javascript:void(0)">+</a>
          </div>
        </div>
        <div class="row button-div">
          <div class="col-md-offset-3 col-md-9">
            <button class="btn btn-default" @click="init_data('timeConfiguration')">CANCEL</button>
            <button class="btn btn-primary" @click="submitTimeConfiguration()">SAVE&APPLY</button>
          </div>
        </div>
      </div>

      <div class="content-title">Restart</div>
      <div class="content-form">
        <div class="row">
          <span class="col-md-3 text-right"><b>Restart The Gateway:</b></span>
          <div class="col-md-9">
            <button class="btn btn-default" @click="rebootSoon()">Restart</button>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Automatic Restart:</b></span>
          <div class="col-md-9">
            <input type="checkbox" v-model="isSetReboot"/>
            <span style="float: left;line-height: 34px;margin-left: 5px;margin-right: 3px;">TIME</span>
            <select class="form-control shortSelect" v-model="cSetHours">
              <option v-for="hour in hoursParams" :value="hour">{{hour}}</option>
            </select>
            <select class="form-control shortSelect" v-model="cSetMinutes">
              <option v-for="minute in minutesParams" :value="minute">{{minute}}</option>
            </select>
          </div>
        </div>
        <div class="row button-div">
          <div class="col-md-offset-3 col-md-9">
            <button class="btn btn-default" @click="init_data('reboot')">CANCEL</button>
            <button class="btn btn-primary" @click="submitAutomaticReboot()">SAVE&APPLY</button>
          </div>
        </div>
      </div>

      <div class="content-title">Logging</div>
      <div class="content-form">
        <div class="row">
          <span class="col-md-3 text-right"><b>Download Logging File:</b></span>
          <div class="col-md-9">
            <button class="btn btn-default" @click="gererateLogging()">Generate logging</button>
            <a :href="logUrl" id="logUrl" download></a>
          </div>
        </div>
      </div>

      <div class="content-title">LED Configuration</div>
      <div class="content-form">
        <div class="row">
          <span class="col-md-3 text-right"><b>LED Indication:</b></span>
          <div class="col-md-9">
            <toggle-button color="#222d32" v-model="isIndication" :sync="true"/>
            <span style="margin-left: 10px;">{{ isIndication ? 'Enable' : 'Disable' }}</span>
          </div>
        </div>
        <div class="row button-div">
          <div class="col-md-offset-3 col-md-9">
            <button class="btn btn-default" @click="init_data('ledConfiguration')">CANCEL</button>
            <button class="btn btn-primary" @click="submitLEDConfiguration()">SAVE&APPLY</button>
          </div>
        </div>
      </div>
    </section>
    <div class="modal fade" id="needLogginModal" data-toggle="modal" data-backdrop="static">
      <div class="modal-dialog" role="document">
        <div class="modal-content" style="width: 900px;">
          <div class="modal-body">
            <p>The Password has been changed successfully! Please sign in again.</p>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-primary" @click="logOut()">ok</button>
          </div>
        </div>
      </div>
    </div>
    <alert_success></alert_success>
    <need_reboot_modal></need_reboot_modal>
    <!-- /.content -->
  </div>
</template>
<style lang="scss">
  #ble-option-content {
    select {
      width: 260px;
    }
    .shortInput {
      width: 80px;
    }
    .shortSelect {
      width: 80px;
    }
    input[type='checkbox'] {
      width: 13px;
      zoom: 180%;
      margin-left: 8px;
    }
  }
</style>
<script>
  import {mapState, mapMutations} from 'vuex'
  import {hoursParams, minutesParams} from '../public.js'
  import {RootUrl, isNotEmpty} from '../public.js'
  import {request} from '../axios'
  import AlertSuccess from '../components/AlertSuccess.vue'
  import NeedRebootModal from '../components/NeedReboot.vue'
  import timeZoneLists from '../lib/timeZoneLists.js'

  export default {
    name: 'system',
    components: {
      'alert_success': AlertSuccess,
      'need_reboot_modal': NeedRebootModal,
    },
    data() {
      return {
        showOldPassword: true,
        oldPassword: '',
        showNewPassword: true,
        newPassword: '',
        showConfirmPassword: true,
        confirmPassword: '',
        oldPasswordError: false,
        newPasswordError: false,
        confirmPasswordError: false,
        isSetReboot: true,
        hoursParams: [],
        cSetHours: '00',
        minutesParams: [],
        cSetMinutes: '00',
        isIndication: '',
        localTime: '',
        timeZoneValue: '',
        timeZoneLists: timeZoneLists,
        ntpEnable: false,
        ntpServer: ['111', '222'],
        logUrl: ''
      }
    },
    created: function () {
      this.hoursParams = hoursParams;
      this.minutesParams = minutesParams;
    },
    mounted: function () {
      this.init_data()
    },
    computed: {
      ...mapState([
        'currentUser'
      ])
    },
    watch: {
      newPassword: function (val) {
        if (val.length < 1 || val.length > 64) {
          this.newPasswordError = true
        } else {
          this.newPasswordError = false
        }
        if (val && this.confirmPassword && val!== this.confirmPassword){
          this.confirmPasswordError = true
        } else {
          this.confirmPasswordError = false
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
      ...mapMutations([
        'signOut'
      ]),
      logOut: function () {
        this.signOut()
        window.location.href = window.location.origin
      },
      setLocalTime: function () {
        var that = this
        var time = new Date().Format('yyyy.MM.dd hh:mm:ss');
        request({
          method: 'post',
          url: (RootUrl + '/sync_time'),
          data: {time: time},
          headers: {'Content-Type': 'application/json'}
        }).then((response) => {
          if (response.data.state.code == 2000) {
            that.init_data()
          }
        })
      },
      init_data: function (type = null) {
        var that = this
        if (!type) {
          request({
            method: 'get',
            url: (RootUrl + '/get_system'),
          }).then((response) => {
            if (response.data.state.code == 2000) {
              let data = response.data.data
              that.localTime = data.time.localtime
              that.timeZoneValue = data.time.timezone
              that.ntpEnable = data.time.ntpenable == '1' ? true : false
              that.ntpServer = data.time.ntpserver
              that.isSetReboot = data.reboot.auto == '1' ? true : false
              that.cSetHours = data.reboot.time.split(":")[0]
              that.cSetMinutes = data.reboot.time.split(":")[1]
              that.isIndication = data.led.enable == '1' ? true : false
            }
          })
        } else if (type == 'adminPassword') {
          this.oldPassword = ''
          this.newPassword = ''
          this.confirmPassword = ''
        } else if (type == 'timeConfiguration') {
          request({
            method: 'get',
            url: (RootUrl + '/get_time'),
          }).then((response) => {
            if (response.data.state.code == 2000) {
              let data = response.data.data
              that.localTime = data.localtime
              that.timeZoneValue = data.timezone
              that.ntpEnable = data.ntpenable == 1 ? true : false
              that.ntpServer = data.ntpserver
            }
          })
        } else if (type == 'reboot') {
          request({
            method: 'get',
            url: (RootUrl + '/get_reboot'),
          }).then((response) => {
            if (response.data.state.code == 2000) {
              let data = response.data.data
              that.isSetReboot = data.auto == '1' ? true : false
              that.cSetHours = data.time.split(":")[0]
              that.cSetMinutes = data.time.split(":")[1]
            }
          })
        } else if (type == 'ledConfiguration') {
          request({
            method: 'get',
            url: (RootUrl + '/get_led'),
          }).then((response) => {
            if (response.data.state.code == 2000) {
              let data = response.data.data
              that.isIndication = data.enable == '1' ? true : false
            }
          })
        }
      },
      addOneServer: function () {
        this.ntpServer.push("")
      },
      removeOneServer: function(i){
        this.ntpServer.splice(i, 1)
      },
      rebootSoon: function () {
        if (confirm("Whether to restart the Gateway immediately？")) {
          request({
            method: 'get',
            url: (RootUrl + '/sys_reboot'),
          }).then((response) => {
            if (response.data.state.code == 2000) {
              ("#needRebootModal").modal('show');
            }
          })
        }
      },
      gererateLogging: function () {
        var that = this
        request({
          method: 'get',
          url: (RootUrl + '/get_syslog'),
        }).then((response) => {
          if (response.data.state.code == 2000) {
            that.logUrl = window.location.origin+'/'+response.data.data.url
            that.$nextTick(function () {
              document.getElementById('logUrl').click()
            })
          }
        })
      },
      submitAdminPasswordForm: function () {
        if (!this.newPassword) {
          this.newPasswordError = true
        }
        if (this.newPassword && !this.newPasswordError && this.confirmPassword === '') {
          this.confirmPasswordError = true
        }
        if (this.newPasswordError || this.confirmPasswordError) {
          return
        }
        var that = this
        request({
          method: 'post',
          url: (RootUrl + '/set_user'),
          data: {
            username: that.currentUser.name,
            oldpasswd: that.oldPassword,
            password: that.newPassword
          },
          headers: {'Content-Type': 'application/json'}
        }).then((response) => {
          if (response.data.state.code == 4080) {
            that.oldPasswordError = true
          } else if (response.data.state.code == 2000) {
            that.init_data()
            $('#needLogginModal').modal('show')
          }
        })
      },
      submitTimeConfiguration: function () {
        var that = this
        if(!isNotEmpty(this.ntpServer)){
          alert("All fields marked with * are required.")
          return
        }
        request({
          method: 'post',
          url: (RootUrl + '/set_time'),
          data: {
            timezone: this.timeZoneValue,
            ntpenable: (this.ntpEnable ? 1 : 0),
            ntpserver: this.ntpServer
          },
          headers: {'Content-Type': 'application/json'}
        }).then((response) => {
          if (response.data.state.code == 2000) {
            that.init_data()
            $("#alertSuccessModal").modal('show')
          }
        })
      },
      submitAutomaticReboot: function () {
        var that = this
        request({
          method: 'post',
          url: (RootUrl + '/set_reboot'),
          data: {
            auto: (this.isSetReboot ? 1 : 0),
            time: this.cSetHours + ":" + this.cSetMinutes,
          },
          headers: {'Content-Type': 'application/json'}
        }).then((response) => {
          if (response.data.state.code == 2000) {
            that.init_data()
            $("#alertSuccessModal").modal('show')
          }
        })
      },
      submitLEDConfiguration: function () {
        var that = this
        request({
          method: 'post',
          url: (RootUrl + '/set_led'),
          data: {
            enable: this.isIndication ? 1 : 0
          },
          headers: {'Content-Type': 'application/json'}
        }).then((response) => {
          if (response.data.state.code == 2000) {
            that.init_data()
            $("#alertSuccessModal").modal('show')
          }
        })
      }
    }
  }
</script>
