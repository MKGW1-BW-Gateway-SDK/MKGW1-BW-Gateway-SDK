<template>
  <div id="wifi-setting-content" class="status-content-wrapper">
    <!-- Content Header (Page header) -->
    <section class="content-header">
      <ol class="breadcrumb">
        <li>
          <v-icon name="luyouqi"></v-icon>
          NETWORK
        </li>
        <li class="active">LAN Setting</li>
      </ol>
    </section>

    <section class="content">
      <div class="content-title">LAN Setting</div>
      <div class="content-form">
        <div class="row">
          <span class="col-md-3 text-right"><b>LAN IP<code>*</code>:</b></span>
          <div class="col-md-9">
            <input class="form-control" type="text" v-model.lazy="lanIp"/>
            <code  v-if="lanIpError" style="line-height: 34px;">
              <i class="glyphicon glyphicon-exclamation-sign"></i>{{ ipError }}</code>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>LAN Mask<code>*</code>:</b></span>
          <div class="col-md-9">
            <input class="form-control" type="text" v-model.lazy="lanMask"/>
            <code  v-if="lanMaskError" style="line-height: 34px;">
              <i class="glyphicon glyphicon-exclamation-sign"></i>{{ ipError }}</code>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>DHCP Server:</b></span>
          <div class="col-md-9">
            <select class="form-control" v-model="dhcpServer" style="width: 80px;">
              <option value="1">YES</option>
              <option value="0">NO</option>
            </select>
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
    <need_reboot_modal></need_reboot_modal>
    <!-- /.content -->
  </div>
</template>
<script>
  import NeedRebootModal from '../components/NeedReboot.vue'
  import {RootUrl, testIsIp} from '../public.js'
  import {request} from '../axios'

  export default {
    name: 'wifi_setting',
    components: {
      'need_reboot_modal': NeedRebootModal,
    },
    data() {
      return {
        lanIp: '',
        lanIpError: false,
        lanMask: '',
        lanMaskError: false,
        dhcpServer: '1',
        ipError: 'The data is incorrect, please check and try again.'
      }
    },
    mounted: function () {
      this.init_data()
    },
    watch: {
      lanIp: function(val){
        if(val){
          if(testIsIp(val)){
            this.lanIpError = false
          }else{
            this.lanIpError = true
          }
        }
      },
      lanMask: function(val){
        if(val){
          if(testIsIp(val)){
            this.lanMaskError = false
          }else{
            this.lanMaskError = true
          }
        }
      },
    },
    methods: {
      init_data: function () {
        request({
          method: 'get',
          url: (RootUrl + '/get_lan'),
        }).then((response) => {
          if (response.data.state.code == 2000) {
            let data = response.data.data
            this.lanIp = data.ipaddr
            this.lanMask = data.netmask
            this.dhcpServer = data.dhcpserver
          }
        })
      },
      submitForm: function () {
        if (!this.lanIp || !this.lanMask) {
          alert('All fields marked with * are required.')
          return
        }
        if(this.lanIpError || this.lanMaskError){
          return
        }
        request({
          method: 'post',
          url: (RootUrl + '/set_lan'),
          data: {
            ipaddr: this.lanIp,
            netmask: this.lanMask,
            dhcpserver: this.dhcpServer,
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
