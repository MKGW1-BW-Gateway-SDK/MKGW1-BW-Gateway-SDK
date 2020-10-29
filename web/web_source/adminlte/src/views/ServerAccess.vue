<template>
  <div id="server-access-content" class="status-content-wrapper">
    <!-- Content Header (Page header) -->
    <section class="content-header">
      <ol class="breadcrumb">
        <li>
          <v-icon name="yunzhujiyunfuwuqijiagou"></v-icon>
          FUNCTION
        </li>
        <li class="active">Server Access</li>
      </ol>
    </section>

    <section class="content">
      <div class="content-title">Server Access</div>
      <div class="content-form">
        <div class="row">
          <span class="col-md-3 text-right"><b>Access Mode:</b></span>
          <div class="col-md-9">
            <select class="form-control" v-model="accessMode">
              <option value="MQTT">MQTT</option>
              <option value="HTTP">HTTP/HTTPS</option>
            </select>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Upload Interval<code>*</code>:</b></span>
          <div class="col-md-9">
            <input class="form-control shortInput" type="tel" v-model.lazy="uploadNum" min="1"/>
            <span style="margin-left: 10px;">Second</span>
            <code v-if="uploadNumError" style="line-height: 34px; margin-left: 20px;">
              <i class="glyphicon glyphicon-exclamation-sign"></i>Please enter an integer which is greater than 0.</code>
          </div>
        </div>
        <template v-if="accessMode == 'MQTT'">
          <div class="row">
            <span class="col-md-3 text-right"><b>Type<code>*</code>:</b></span>
            <div class="col-md-9">
              <select class="form-control" v-model="serverType">
                <option value="TCP">TCP</option>
                <option value="SSL">SSL</option>
              </select>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>Host/IP<code>*</code>:</b></span>
            <div class="col-md-9">
              <input type="text" class="form-control" v-model.lazy="hostIp"/>
              <code v-if="hostIpError" style="line-height: 34px;">
                <i class="glyphicon glyphicon-exclamation-sign"></i>{{ ipError }}</code>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>Port<code>*</code>:</b></span>
            <div class="col-md-9">
              <input type="tel" class="form-control" v-model.lazy="serverPort" min="0" max="65535"/>
              <code v-if="serverPortError" style="line-height: 34px;">
                <i class="glyphicon glyphicon-exclamation-sign"></i>Please enter an imteger between 0 and 65535!</code>
            </div>
          </div>

          <template v-if="serverType=='SSL'">
            <div class="row">
              <span class="col-md-3 text-right"><b>Certification Type<code>*</code>:</b></span>
              <div class="col-md-9">
                <select class="form-control" v-model="certType">
                  <option value="CA_CERT">CA certificate</option>
                  <option value="CA_SIGN">CA signed server certificate</option>
                  <option value="SE_SIGN">Self signed certificates</option>
                </select>
              </div>
            </div>
            <div class="row" v-if="certType == 'CA_CERT'">
              <span class="col-md-3 text-right"><b>CA Certificate File<code>*</code>:</b></span>
              <div class="col-md-9">
                <span>{{ sca }}</span>
                <input type="file" style="margin-top: 6px;" ref="fCaCert" @change="handleFileUpload('fCaCert')"/>
                <code v-if="fCaCertError" style="line-height: 34px;">
                  <i class="glyphicon glyphicon-exclamation-sign"></i>{{ fileError }}</code>
              </div>
            </div>
            <template v-if="certType == 'SE_SIGN'">
              <div class="row">
                <span class="col-md-3 text-right"><b>CA File<code>*</code>:</b></span>
                <div class="col-md-9">
                  <span>{{ ca }}</span>
                  <input type="file" style="margin-top: 6px;" ref="fTruBuyC" @change="handleFileUpload('fTruBuyC')"/>
                  <code v-if="fTruBuyCError" style="line-height: 34px;">
                    <i class="glyphicon glyphicon-exclamation-sign"></i>{{ fileError }}</code>
                </div>
              </div>
              <div class="row">
                <span class="col-md-3 text-right"><b>Client Certiflcate File<code>*</code>:</b></span>
                <div class="col-md-9">
                  <span>{{ cert }}</span>
                  <input type="file" style="margin-top: 6px;" ref="fForCToPToS"
                         @change="handleFileUpload('fForCToPToS')"/>
                  <code v-if="fForCToPToSError" style="line-height: 34px;">
                    <i class="glyphicon glyphicon-exclamation-sign"></i>{{ fileError }}</code>
                </div>
              </div>
              <div class="row">
                <span class="col-md-3 text-right"><b>Client Key File<code>*</code>:</b></span>
                <div class="col-md-9">
                  <span>{{ key }}</span>
                  <input type="file" style="margin-top: 6px;" ref="clientPKey"
                         @change="handleFileUpload('clientPKey')"/>
                  <code v-if="clientPKeyError" style="line-height: 34px;">
                    <i class="glyphicon glyphicon-exclamation-sign"></i>{{ fileError }}</code>
                </div>
              </div>
            </template>
          </template>

          <div class="row">
            <span class="col-md-3 text-right"><b>Client ID:</b></span>
            <div class="col-md-9">
              <input type="text" class="form-control" v-model="clientId" minlength="1" maxlength="64"/>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>QoS<code v-if="serverType=='TCP'">*</code>:</b></span>
            <div class="col-md-9">
              <select class="form-control" v-model="qos">
                <option value="0">0</option>
                <option value="1">1</option>
                <option value="2">2</option>
              </select>
            </div>
          </div>
        </template>
        <div class="row" v-if="accessMode == 'HTTP'">
          <span class="col-md-3 text-right"><b>URL<code>*</code>:</b></span>
          <div class="col-md-9">
            <input type="text" class="form-control" v-model.lazy="serverUrl"/>
            <code v-if="serverUrlError" style="line-height: 34px;">
              <i class="glyphicon glyphicon-exclamation-sign"></i>The format is incorrect, please check and try again.</code>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Username:</b></span>
          <div class="col-md-9">
            <input type="text" class="form-control" v-model="userName"/>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Password:</b></span>
          <div class="col-md-9">
            <div class="password-input" v-if="showNewPassword">
              <input class="form-control" type="text" v-model.lazy="password"/>
              <a class="glyphicon glyphicon-eye-open" href="javascript:void(0)"
                 @click="showNewPassword = !showNewPassword"></a>
            </div>
            <div class="password-input" v-else>
              <input class="form-control" type="password" v-model.lazy="password"/>
              <a class="glyphicon glyphicon-eye-close" href="javascript:void(0)"
                 @click="showNewPassword = !showNewPassword"></a>
            </div>
          </div>
        </div>
        <template v-if="accessMode == 'MQTT'">
          <div class="row">
            <span class="col-md-3 text-right"><b>Gateway Publish Topic<code>*</code>:</b></span>
            <div class="col-md-9">
              <input type="text" class="form-control" v-model="gatewayPubTop"/>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>Gateway Subscribe Topic:</b></span>
            <div class="col-md-9">
              <input type="text" class="form-control" v-model="gatewaySubTop"/>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>Gateway Manage Publish Topic:</b></span>
            <div class="col-md-9">
              <input type="text" class="form-control" v-model="gatewayMPubTop"/>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>Gateway Manage Subscribe Topic:</b></span>
            <div class="col-md-9">
              <input type="text" class="form-control" v-model="gatewayMSubTop"/>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>HeartBeat:</b></span>
            <div class="col-md-9">
              <select class="form-control shortSelect" v-model="heartBeat" :disabled="!checkHeartBeat">
                <option value="30">30S</option>
                <option value="60">60S</option>
                <option value="90">90S</option>
                <option value="120">120S</option>
                <option value="150">150S</option>
                <option value="180">180S</option>
              </select>
              <input type="checkbox" v-model="checkHeartBeat"/>
            </div>
          </div>
        </template>
        <div class="row button-div">
          <div class="col-md-offset-3 col-md-9">
            <button class="btn btn-default" @click="init_data()">CANCEL</button>
            <button class="btn btn-primary" @click="submitForm()">SAVE&APPLY</button>
          </div>
        </div>
      </div>
    </section>
    <!-- /.content -->
    <alert_success></alert_success>
  </div>
</template>
<style lang="scss">
  #server-access-content {
    input, select {
      width: 350px;
    }
    .shortInput {
      width: 80px;
    }
    .shortSelect {
      width: 270px;
    }
    input[type='checkbox'] {
      width: 13px;
      zoom: 180%;
      margin-left: 8px;
    }
  }
</style>
<script>
  import {RootUrl, RootSetUrl, testIsIp, testIshost, testIsUrl} from '../public.js'
  import {request} from '../axios'
  import AlertSuccess from '../components/AlertSuccess.vue'

  export default {
    name: 'server_access',
    components: {
      'alert_success': AlertSuccess,
    },
    data() {
      return {
        accessMode: 'MQTT',
        uploadNum: 1,
        uploadNumError: false,
        showConfirmPassword: true,
        serverType: 'TCP',
        hostIp: '',
        hostIpError: false,
        serverPort: '',
        serverPortError: false,
        clientId: '',
        qos: 0,
        userName: '',
        password: '',
        keyPassword: '',
        showNewPassword: true,
        showKeyPassword: true,
        gatewayPubTop: '',
        gatewayMPubTop: '',
        gatewaySubTop: '',
        gatewayMSubTop: '',
        heartBeat: '60',
        checkHeartBeat: true,
        fTruBuyC: '',
        fTruBuyCError: false,
        fForCToPToS: '',
        fForCToPToSError: false,
        clientPKey: '',
        clientPKeyError: false,
        fCaCert: '',
        fCaCertError: false,
        mqttParams: {},
        httpParams: {},
        serverUrl: '',
        serverUrlError: false,
        ca: '',
        cert: '',
        key: '',
        sca: '',
        ipError: 'The data is incorrect, please check and try again.',
        certType: 'CA_CERT',
        fileError: 'Please choose a file.'
      }
    },
    mounted: function () {
      this.init_data()
    },
    watch: {
      accessMode: function () {
        this.update_params()
      },
      serverUrl: function(val){
        if (val !== '') {
          if (testIsUrl(val)) {
            this.serverUrlError = false
          } else {
            this.serverUrlError = true
          }
        } else {
          this.serverUrlError = false
        }
      },
      hostIp: function (val) {
        if (val !== '') {
          if (testIsIp(val) || testIshost(val)) {
            this.hostIpError = false
          } else {
            this.hostIpError = true
          }
        } else {
          this.hostIpError = false
        }
      },
      serverPort: function (val) {
        if (val !== '') {
          if (val % 1 !== 0 || val < 0 || val > 65535) {
            this.serverPortError = true
          } else {
            this.serverPortError = false
          }
        } else {
          this.serverPortError = false
        }
      },
      uploadNum: function (val) {
        if (val !== '') {
          if (val % 1 !== 0 || val < 1) {
            this.uploadNumError = true
          } else {
            this.uploadNumError = false
          }
        } else {
          this.uploadNumError = false
        }
      },
      certType: function (val) {
        if (val == 'CA_CERT') {
          this.fTruBuyCError = false
          this.fForCToPToSError = false
          this.clientPKeyError = false
          if (!this.sca && (this.fCaCert === undefined || this.fCaCert === '')) {
            this.fCaCertError = true
          } else {
            this.fCaCertError = false
          }
        } else if (val == 'CA_SIGN') {
          this.fTruBuyCError = false
          this.fForCToPToSError = false
          this.clientPKeyError = false
        } else {
          if (!this.ca && (this.fTruBuyC === undefined || this.fTruBuyC === '')) {
            this.fTruBuyCError = true
          } else {
            this.fTruBuyCError = false
          }
          if (!this.cert && (this.fForCToPToS === undefined || this.fForCToPToS === '')) {
            this.fForCToPToSError = true
          } else {
            this.fForCToPToSError = false
          }
          if (!this.key && (this.clientPKey === undefined || this.clientPKey === '')) {
            this.clientPKeyError = true
          } else {
            this.clientPKeyError = false
          }
        }
      }
    },
    methods: {
      init_data: function () {
        let that = this
        request({
          method: 'get',
          url: (RootUrl + '/get_service'),
        }).then((response) => {
          if (response.data.state.code == 2000) {
            let data = response.data.data
            that.accessMode = data.accessmode
            that.mqttParams = data.mqtt
            that.httpParams = data.http
            that.fTruBuyC = ''
            that.fCaCert = ''
            that.fForCToPToS = ''
            that.clientPKey = ''
            that.$nextTick(function () {
              that.update_params()
            })
          }
        })
      },
      update_params: function () {
        if (this.accessMode == 'MQTT') {
          this.uploadNum = this.mqttParams.interval
          this.serverType = this.mqttParams.type
          this.hostIp = this.mqttParams.host
          this.serverPort = this.mqttParams.port
          this.clientId = this.mqttParams.clientid
          this.qos = this.mqttParams.qos
          this.userName = this.mqttParams.username
          this.password = this.mqttParams.password
          this.gatewayPubTop = this.mqttParams.pubtopic
          this.gatewayMPubTop = this.mqttParams.msgpubtopic
          this.gatewaySubTop = this.mqttParams.subtopic
          this.gatewayMSubTop = this.mqttParams.msgsubtopic
          this.heartBeat = this.mqttParams.heartbeat
          this.checkHeartBeat = this.mqttParams.hbenable == '1' ? true : false
          this.certType = this.mqttParams.certtype || 'CA_CERT'
          this.sca = this.mqttParams.sca
          this.ca = this.mqttParams.ca
          this.cert = this.mqttParams.cert
          this.key = this.mqttParams.key
        } else {
          this.uploadNum = this.httpParams.interval
          this.userName = this.httpParams.username
          this.password = this.httpParams.password
          this.serverUrl = this.httpParams.url
        }
      },
      handleFileUpload: function (fileName) {
        this.$data[fileName] = this.$refs[fileName].files[0];
        if (this.$data[fileName] === undefined) {
          this.$data[fileName + 'Error'] = true
        } else {
          this.$data[fileName + 'Error'] = false
        }
      },
      submitForm: function () {
        var that = this
        if (!this.uploadNum) {
          alert('All fields marked with * are required.')
          return
        }
        if (this.uploadNumError) {
          return
        }
        if (this.accessMode == 'HTTP') {
          if (!this.serverUrl) {
            alert('All fields marked with * are required.')
            return
          }
          if (this.serverUrlError) {
            return
          }
        } else if (this.accessMode == 'MQTT') {
          if (!this.hostIp || !this.serverPort || !this.gatewayPubTop) {
            alert('All fields marked with * are required.')
            return
          }
          if (this.hostIpError || this.serverPortError) {
            return
          }
          if (this.serverType == 'SSL') {
            if (this.fCaCertError || this.fTruBuyCError || this.fForCToPToSError || this.clientPKeyError) {
              return
            }
          }
        }
        if (this.newPassword && !this.newPasswordError && this.confirmPassword === '') {
          this.confirmPasswordError = true
        }
        if (this.newPasswordError || this.confirmPasswordError) {
          return
        }
        let formData = new FormData();
        let mqtt = {
          interval: this.uploadNum,
          type: this.serverType,
          host: this.hostIp,
          port: this.serverPort,
          clientid: this.clientId,
          qos: this.qos,
          username: this.userName,
          password: this.password,
          pubtopic: this.gatewayPubTop,
          msgpubtopic: this.gatewayMPubTop,
          subtopic: this.gatewaySubTop,
          msgsubtopic: this.gatewayMSubTop,
          heartbeat: this.heartBeat,
          hbenable: this.checkHeartBeat ? 1 : 0,
          ca: this.fTruBuyC,
          cert: this.fForCToPToS,
          key: this.clientPKey,
          sca: this.fCaCert,
          certtype: this.certType
        }
        let http = {
          interval: this.uploadNum,
          username: this.userName,
          password: this.password,
          url: this.serverUrl
        }
        let data = JSON.stringify({accessmode: this.accessMode, mqtt: mqtt, http: http})
        formData.append('data', data);
        formData.append('sca', this.fCaCert);
        formData.append('ca', this.fTruBuyC);
        formData.append('cert', this.fForCToPToS);
        formData.append('key', this.clientPKey);
        request({
          method: 'post',
          url: (RootSetUrl + '/set_service'),
          data: formData,
          headers: {'Content-Type': 'multipart/form-data'}
        }).then(function () {
          $("#alertSuccessModal").modal('show')
          that.init_data()
        }).catch(function () {
          console.log('FAILURE!!');
        });
      }
    }
  }
</script>
