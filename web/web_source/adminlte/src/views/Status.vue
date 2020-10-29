<template>
  <div id="status-content" class="status-content-wrapper">
    <!-- Content Header (Page header) -->
    <section class="content-header">
      <ol class="breadcrumb">
        <li class="active">
          <v-icon name="fazhuangtai"></v-icon>
          STATUS
        </li>
        <li class="pull-right refresh" style=":before: {content: none}">
          <a href="javascript:void(0)" @click="refreshStatus">
            <img :class="rotatefresh" src="../assets/img/refresh.png" style="width: 22px;margin-right: 5px;"/></a>
          <span style="line-height: 22px;">REFRESH</span>
        </li>
      </ol>
    </section>

    <section class="content">
      <div class="content-title">Device Info</div>
      <div class="content-form">
        <p class="row">
          <span class="col-md-3 text-right"><b>User Name:</b></span>
          <span>{{ username }}</span>
        </p>
        <p class="row">
          <span class="col-md-3 text-right"><b>Geteway SSID:</b></span>
          <span style="margin-right: 10px;">{{ ssid }}</span>
          <router-link to="wifi_setting"><i class="glyphicon glyphicon-edit"></i></router-link>
        </p>
        <p class="row">
          <span class="col-md-3 text-right"><b>MAC Address:</b></span>
          <span>{{ macaddr }}</span>
        </p>
        <p class="row">
          <span class="col-md-3 text-right"><b>Firmware Version:</b></span>
          <span>{{ sysversion }}</span>
        </p>
        <p class="row">
          <span class="col-md-3 text-right"><b>Local Time:</b></span>
          <span style="margin-right: 10px;">{{ localtime }}</span>
          <router-link to="system"><i class="glyphicon glyphicon-edit"></i></router-link>
        </p>
        <p class="row">
          <span class="col-md-3 text-right"><b>Uptime:</b></span>
          <span>{{ show_uptime }}</span>
        </p>
        <p class="row">
          <span class="col-md-3 text-right"><b>CPU Usage:</b></span>
          <span>{{ cpuinfo }}</span>
        </p>
        <p class="row">
          <span class="col-md-3 text-right"><b>Memory Usage:</b></span>
          <span>{{ meminfo }}</span>
        </p>
      </div>

      <div class="content-title">Network Info</div>
      <div class="content-form">
        <p class="row">
          <span class="col-md-3 text-right"><b>Wireless Standard:</b></span>
          <span>{{ wifimode }}</span>
        </p>
        <p class="row">
          <span class="col-md-3 text-right"><b>Internet Mode:</b></span>
          <span>{{ wanmode }}</span>
          <span :class="[wanlink==1 ? 'green' : 'red', 'dian']"></span>
          <router-link to="internet_setting"><i class="glyphicon glyphicon-edit"></i></router-link>
        </p>
        <p class="row">
          <span class="col-md-3 text-right"><b>WAN IP:</b></span>
          <span>{{ wanip }}</span>
        </p>
        <p class="row">
          <span class="col-md-3 text-right"><b>LAN IP:</b></span>
          <span>{{ lanip }}</span>
        </p>
        <p class="row">
          <span class="col-md-3 text-right"><b>Channel/Frequency:</b></span>
          <span style="margin-right: 10px;">{{ channel }}</span>
        </p>
        <p class="row">
          <span class="col-md-3 text-right"><b>Service Access:</b></span>
          <span >{{ access }}</span>
          <span :class="[aclink==1 ? 'green' : 'red', 'dian']"></span>
          <router-link to="server_access"><i class="glyphicon glyphicon-edit"></i></router-link>
        </p>
      </div>
    </section>
    <!-- /.content -->
  </div>
</template>
<script>
  import {RootUrl} from '../public.js'
  import {request} from '../axios'

  export default {
    name: 'status',
    data() {
      return {
        username: '',
        ssid: '',
        macaddr: '',
        sysversion: '',
        localtime: '',
        uptime: '',
        cpuinfo: '',
        meminfo: '',
        wifimode: '',
        wanmode: '',
        wanip: '',
        wanlink: '',
        lanip: '',
        channel: '',
        access: '',
        aclink: '',
        rotatefresh: ''
      }
    },
    computed: {
      show_uptime: function () {
        if (this.uptime) {
          var uptime = ''
          var h = parseInt(this.uptime / 3600)
          uptime = uptime + h + 'h '
          var m = parseInt(this.uptime % 3600 / 60)
          uptime = m > 0 ? uptime + m + 'min ' : uptime
          var s = this.uptime % 3600 % 60
          uptime = s > 0 ? uptime + s + 's' : uptime
          return uptime
        } else {
          return ''
        }
      }
    },
    mounted: function () {
      this.init_data()
    },
    methods:{
      init_data: function(){
        var that = this;
        request({
          method: 'get',
          url: (RootUrl + '/sysstatus'),
        }).then((response) => {
          if (response.data.state.code == 2000) {
            let data = response.data.data
            that.username = data.deviceinfo.username
            that.ssid = data.deviceinfo.ssid
            that.macaddr = data.deviceinfo.macaddr
            that.sysversion = data.deviceinfo.sysversion
            that.localtime = data.deviceinfo.localtime
            that.uptime = data.deviceinfo.uptime
            that.cpuinfo = data.deviceinfo.cpuinfo
            that.meminfo = data.deviceinfo.meminfo
            that.wifimode = data.networkinfo.wifimode
            that.wanmode = data.networkinfo.wanmode
            that.wanip = data.networkinfo.wanip
            that.wanlink = data.networkinfo.wanlink
            that.lanip = data.networkinfo.lanip
            that.channel = data.networkinfo.channel
            that.access = data.networkinfo.access
            that.aclink = data.networkinfo.aclink
          }
          setTimeout(function () {
            that.rotatefresh = ''
          }, 1000);
        })
      },
      refreshStatus: function(){
        var that = this
        this.rotatefresh = 'rotatefresh'
        this.init_data()
      }
    }
  }
</script>
