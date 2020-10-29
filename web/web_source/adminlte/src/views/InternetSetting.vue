<template>
  <div id="internet-setting-content" class="status-content-wrapper">
    <!-- Content Header (Page header) -->
    <section class="content-header">
      <ol class="breadcrumb">
        <li>
          <v-icon name="luyouqi"></v-icon>
          NETWORK
        </li>
        <li class="active">Internet Setting</li>
      </ol>
    </section>

    <section class="content">
      <div class="content-title">Internet Setting</div>
      <div class="content-form">
        <div class="row">
          <span class="col-md-3 text-right"><b>Internet Connection Mode:</b></span>
          <div class="col-md-9 has_explain_div">
            <select class="form-control" v-model="conMode">
              <option value="ETH">ETH</option>
              <option value="WIFI">WIFI</option>
            </select>
            <div class="explain">
              <p>ETH:Gateway accesses the Internet via ETH cable.</p>
              <p>WIFI:Gateway accesses the Internet through the router.</p>
            </div>
          </div>
        </div>
        <template v-if="conMode == 'WIFI'">
          <div class="row">
            <span class="col-md-3 text-right"><b>WIFI SSID<code>*</code>:</b></span>
            <div class="col-md-9">
              <input class="form-control" type="text" v-model="wifiSsid"/>
              <button class="btn btn-default" @click="searchWifiSsid()"><i class="glyphicon glyphicon-search"></i>
              </button>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>Encrypt:</b></span>
            <div class="col-md-9">
              <select class="form-control" v-model="encrypt">
                <option v-for="list in encryptLists" :value="list">{{ list }}</option>
              </select>
            </div>
          </div>
          <div class="row" v-if="encrypt!= 'NONE'">
            <span class="col-md-3 text-right"><b>Password<code>*</code>:</b></span>
            <div class="col-md-9">
              <div class="password-input" v-if="showPassword">
                <input class="form-control" type="text" v-model.lazy="password" :placeholder="placeholder"/>
                <a class="glyphicon glyphicon-eye-open" href="javascript:void(0)"
                   @click="showPassword = !showPassword"></a>
              </div>
              <div class="password-input" v-else>
                <input class="form-control" type="password" v-model.lazy="password" :placeholder="placeholder"/>
                <a class="glyphicon glyphicon-eye-close" href="javascript:void(0)"
                   @click="showPassword = !showPassword"></a>
              </div>
              <code v-if="passwordError">
                <i class="glyphicon glyphicon-exclamation-sign"></i>{{ placeholder }}</code>
            </div>
          </div>
        </template>
        <div class="row">
          <span class="col-md-3 text-right"><b>Connection Type:</b></span>
          <div class="col-md-9">
            <select class="form-control" v-model="connectionType">
              <option value="dhcp">Automatic IP</option>
              <option value="static">Static IP</option>
            </select>
          </div>
        </div>
        <template v-if="connectionType == 'static'">
          <div class="row">
            <span class="col-md-3 text-right"><b>WAN IP<code>*</code>:</b></span>
            <div class="col-md-9">
              <input type="text" v-model.lazy="wanIp" class="form-control"/>
              <code  v-if="wanIpError" style="line-height: 34px;">
                <i class="glyphicon glyphicon-exclamation-sign"></i>{{ ipError }}</code>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>Subnet Mask<code>*</code>:</b></span>
            <div class="col-md-9">
              <input type="text" v-model.lazy="subMask" class="form-control"/>
              <code  v-if="subMastError" style="line-height: 34px;">
                <i class="glyphicon glyphicon-exclamation-sign"></i>{{ ipError }}</code>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>Gateway IP<code>*</code>:</b></span>
            <div class="col-md-9">
              <input type="text" v-model.lazy="gateWayIp" class="form-control"/>
              <code  v-if="gateWayIpError" style="line-height: 34px;">
                <i class="glyphicon glyphicon-exclamation-sign"></i>{{ ipError }}</code>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>Primary DNS<code>*</code>:</b></span>
            <div class="col-md-9">
              <input type="text" v-model.lazy="priDns" class="form-control"/>
              <code  v-if="priDnsError" style="line-height: 34px;">
                <i class="glyphicon glyphicon-exclamation-sign"></i>{{ ipError }}</code>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>Secondary DNS:</b></span>
            <div class="col-md-9">
              <input type="text" v-model.lazy="secDns" class="form-control"/>
              <code  v-if="secDnsError" style="line-height: 34px;">
                <i class="glyphicon glyphicon-exclamation-sign"></i>{{ ipError }}</code>
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
    <div class="modal fade" id="wifiSsidSearchModal" data-toggle="modal">
      <div class="modal-dialog" role="document">
        <div class="modal-content" style="width: 900px;">
          <div class="modal-body">
            <table class="table table-bordered table-striped">
              <thead>
              <tr>
                <th>SSID</th>
                <th>MAC Address</th>
                <th>Encrypt</th>
                <th>Signal(%)</th>
                <th>Channel</th>
              </tr>
              </thead>
              <tbody>
              <tr v-for="list in wifiSsidLists" @click="chooseWifiSsid(list)">
                <td>{{list.ssid}}</td>
                <td>{{list.macaddr}}</td>
                <td>{{list.encrypt}}</td>
                <td>{{list.signal}}</td>
                <td>{{list.channel}}</td>
              </tr>
              </tbody>
            </table>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-default" data-dismiss="modal">CANCEL</button>
            <button type="button" class="btn btn-primary" @click="searchWifiSsid()">RESCAN</button>
          </div>
        </div>
      </div>
    </div>
    <need_reboot_modal></need_reboot_modal>
    <!-- /.content -->
  </div>
</template>
<script>
  import NeedRebootModal from '../components/NeedReboot.vue'
  import {RootUrl, testIsOkPassword, testIsIp} from '../public.js'
  import encryptLists from '../lib/encryptLists.js'
  import {request} from '../axios'
  import Need_reboot_modal from "../components/NeedReboot.vue";

  export default {
    name: 'internet_setting',
    components: {
      Need_reboot_modal,
      'need_reboot_modal': NeedRebootModal,
    },
    data() {
      return {
        conMode: 'ETH',
        encrypt: 'WPA1PSKWPA2PSK/TKIPAES',
        encryptLists: encryptLists,
        showPassword: true,
        password: '',
        wifiSsidLists: [],
        wifiObj: {},
        wifiSsid: '',
        connectionType: 'dhcp',
        wanIp: '',
        subMask: '',
        gateWayIp: '',
        priDns: '',
        secDns: '',
        passwordError: false,
        wanIpError: false,
        subMastError: false,
        gateWayIpError: false,
        priDnsError: false,
        secDnsError: false,
        d_placeholder: '8-63 characters',
        w_placeholder: '5|13 ascii characters or 10|26 hex characters',
        ipError: 'The data is incorrect, please check and try again.'
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
      wanIp: function(val){
        if(val){
          if(testIsIp(val)){
            this.wanIpError = false
          }else{
            this.wanIpError = true
          }
        }
      },
      subMask: function(val){
        if(val){
          if(testIsIp(val)){
            this.subMastError = false
          }else{
            this.subMastError = true
          }
        }
      },
      gateWayIp: function(val){
        if(val){
          if(testIsIp(val)){
            this.gateWayIpError = false
          }else{
            this.gateWayIpError = true
          }
        }
      },
      priDns: function(val){
        if(val){
          if(testIsIp(val)){
            this.priDnsError = false
          }else{
            this.priDnsError = true
          }
        }
      },
      secDns: function(val){
        if(val){
          if(testIsIp(val)){
            this.secDnsError = false
          }else{
            this.secDnsError = true
          }
        }
      },
      conMode: function (val) {
        if (val == 'ETH') {
          this.wifiSsid = ''
          if(!this.encrypt){
            this.encrypt = 'wpa-psk[tkip]'
          }
          this.password = ''
        }else if(val == 'WIFI'){
          if(!this.encrypt) {
            this.encrypt = 'WPA2PSK/AES'
          }
        }
      },
      password: function (val) {
        if(val){
          if(this.encrypt == 'WEP'){
            if(!testIsOkPassword(val)){
              this.passwordError = true
            }else{
              this.passwordError = false
            }
          }else{
            if(val.length < 8 || val.length > 63){
              this.passwordError = true
            }else{
              this.passwordError = false
            }
          }
        }else{
          this.passwordError = false
        }
      },
    },
    methods: {
      init_data: function () {
        var that = this
        request({
          method: 'get',
          url: (RootUrl + '/get_wan'),
        }).then((response) => {
          if (response.data.state.code == 2000) {
            let data = response.data.data
            that.conMode = data.wanmode
            that.wifiSsid = data.wanssid
            that.password = data.wanpassword
            that.connectionType = data.proto
            that.wanIp = data.ipaddr
            that.subMask = data.netmask
            that.gateWayIp = data.gateway
            that.priDns = data.firdns
            that.secDns = data.secdns
            that.$nextTick(function(){
              that.encrypt = data.wanencrypt
            })
          }
        })
      },
      chooseWifiSsid: function (list) {
        this.wifiObj = list
        this.wifiSsid = list.ssid
        this.encrypt = list.encrypt
        this.$nextTick(function () {
          $("#wifiSsidSearchModal").modal('hide')
        })
      },
      searchWifiSsid: function () {
        var that = this
        $("#wifiSsidSearchModal").modal('show')
        that.wifiSsidLists = []
        request({
          method: 'get',
          url: (RootUrl + '/get_wifisite'),
        }).then((response) => {
          if (response.data.state.code == 2000) {
            that.wifiSsidLists = response.data.data.site
          }
        })
      },
      submitForm: function () {
        if (this.conMode == 'WIFI') {
          if (!this.wifiSsid) {
            alert('All fields marked with * are required.')
            return
          }
          if (this.encrypt != 'NONE') {
            if (!this.password) {
              alert('All fields marked with * are required.')
              return
            } else if (this.passwordError) {
              return
            }
          }
        }
        if (this.connectionType == 'static') {
          if (!this.wanIp || !this.subMask || !this.gateWayIp || !this.priDns) {
            alert('All fields marked with * are required.')
            return
          }
          if(this.wanIpError || this.subMastError || this.gateWayIpError || this.priDnsError || this.secDnsError){
            return
          }
        }
        request({
          method: 'post',
          url: (RootUrl + '/set_wan'),
          data: {
            wanmode: this.conMode,
            wanssid: this.wifiSsid,
            wanencrypt: this.encrypt,
            wanpassword: this.password,
            proto: this.connectionType,
            ipaddr: this.wanIp,
            netmask: this.subMask,
            gateway: this.gateWayIp,
            firdns: this.priDns,
            secdns: this.secDns
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
