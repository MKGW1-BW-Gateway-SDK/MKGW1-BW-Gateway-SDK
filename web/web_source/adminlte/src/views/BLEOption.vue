<template>
  <div id="ble-option-content" class="status-content-wrapper">
    <!-- Content Header (Page header) -->
    <section class="content-header">
      <ol class="breadcrumb">
        <li>
          <v-icon name="yunzhujiyunfuwuqijiagou"></v-icon>
          FUNCTION
        </li>
        <li class="active">BLE Option</li>
      </ol>
    </section>

    <section class="content">
      <div class="content-title">BLE Option</div>
      <div class="content-form">
        <div class="row">
          <span class="col-md-3 text-right"><b>BLE Scanning:</b></span>
          <div class="col-md-9">
            <toggle-button color="#222d32" v-model="isScaning" :sync="true"/>
            <span style="margin-left: 10px;">{{ isScaning ? 'Enable' : 'Disable' }}</span>
          </div>
        </div>
        <template v-if="isScaning">
          <!--<div class="row">-->
            <!--<span class="col-md-3 text-right"><b>BLE Scan time(Second)<code>*</code>:</b></span>-->
            <!--<div class="col-md-9">-->
              <!--<input type="tel" class="form-control shortInput" v-model.lazy="scanTime" :disabled="alwaysScan"/>-->
              <!--<input type="checkbox" style="margin-left: 10px;" v-model="alwaysScan"/>-->
              <!--<span style="margin-left: 5px;">Always Scanning</span>-->
              <!--<code  v-if="scanTimeError" style="line-height: 34px; margin-left: 20px;">-->
                <!--<i class="glyphicon glyphicon-exclamation-sign"></i>Please enter an integer which is greater than 0.</code>-->
            <!--</div>-->
          <!--</div>-->
          <div class="row">
            <span class="col-md-3 text-right"><b>RSSI Filter(dBm):</b></span>
            <div class="col-md-9">
              <input type="tel" class="form-control" placeholder="-100~0" v-model.lazy="rssi" />
              <code  v-if="rssiError" style="line-height: 34px;">
                <i class="glyphicon glyphicon-exclamation-sign"></i>Please enter an integer between -100 and 0.</code>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>BLE Name&MAC Filter:</b></span>
            <div class="col-md-9">
              <input type="text" class="form-control" v-model="mac" maxlength="30"/>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>Cache Time(0~60s)<code>*</code>:</b></span>
            <div class="col-md-9">
              <input type="tel" class="form-control" v-model.lazy="cacheTime" placeholder="0~60"/>
              <code  v-if="cacheTimeError" style="line-height: 34px;">
                <i class="glyphicon glyphicon-exclamation-sign"></i>Please enter an integer between 0 and 60.</code>
            </div>
          </div>
          <div class="row">
            <span class="col-md-3 text-right"><b>BLE Data Format:</b></span>
            <div class="col-md-9">
              <p>
                <input type="checkbox" v-model="row_data">
                <span>Raw Data</span>
              </p>
              <p>
                <input type="checkbox" v-model="iBeacon">
                <span>iBeacon</span>
              </p>
              <p>
                <input type="checkbox" v-model="MkiBeacon">
                <span>MkiBeacon</span>
              </p>
              <p>
                <input type="checkbox" v-model="MkiBeacon3Axis">
                <span>MkiBeacon&3Axis</span>
              </p>
              <p>
                <input type="checkbox" v-model="MkBeaconX3Axis">
                <span>BeaconX Pro-3Axis</span>
              </p>
              <p>
                <input type="checkbox" v-model="MkBeaconXHT">
                <span>BeaconX Pro-T&H</span>
              </p>
              <p>
                <input type="checkbox" v-model="EddystoneUID">
                <span>Eddystone-UID</span>
              </p>
              <p>
                <input type="checkbox" v-model="EddystoneTLM">
                <span>Eddystone-TLM</span>
              </p>
              <p>
                <input type="checkbox" v-model="EddystoneURL">
                <span>Eddystone-URL</span>
              </p>
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
  #ble-option-content {
    select {
      width: 260px;
    }
    .shortInput {
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
  import {RootUrl} from '../public.js'
  import {request} from '../axios'
  import AlertSuccess from '../components/AlertSuccess.vue'
  import bleOption from '../lib/bleOption.js'

  export default {
    name: 'ble_option',
    components: {
      'alert_success': AlertSuccess,
    },
    data() {
      return {
        isScaning: '',
//        scanTime: '',
//        scanTimeError: false,
//        alwaysScan: false,
        rssi: '',
        rssiError: false,
        mac: '',
        uuid: '',
        cacheTime: '',
        cacheTimeError: false,
        row_data: '',
        iBeacon: '',
        MkiBeacon: '',
        MkiBeacon3Axis: '',
        MkBeaconX3Axis: '',
        MkBeaconXHT: '',
        EddystoneUID: '',
        EddystoneTLM: '',
        EddystoneURL: '',
        bleOption: bleOption
      }
    },
    watch: {
      cacheTime: function(val){
        if(val !== ''){
          if(val % 1 !== 0 || val < 0 || val > 60){
            this.cacheTimeError = true
          }else{
            this.cacheTimeError = false
          }
        }else{
          this.cacheTimeError = false
        }
      },
      rssi: function(val){
        if(val !== ''){
          if(val % 1 !== 0 || val > 0 || val < -100){
            this.rssiError = true
          }else{
            this.rssiError = false
          }
        }else{
          this.rssiError = false
        }
      },
//      scanTime: function(val){
//        if(val !== ''){
//          if(!this.alwaysScan && (val % 1 !== 0 || val < 1)){
//            this.scanTimeError = true
//          }else{
//            this.scanTimeError = false
//          }
//        }else{
//          this.scanTimeError = false
//        }
//      },
//      alwaysScan: function(val){
//        if(val){
//          this.scanTime = 0
//          this.scanTimeError = false
//        }else{
//          if(this.scanTime!==''){
//            if(this.scanTime % 1 !== 0 || this.scanTime < 1){
//              this.scanTimeError = true
//            }
//          }
//        }
//      }
    },
    created: function () {
      this.init_data()
    },
    methods: {
      init_data: function () {
        var that = this
        request({
          method: 'get',
          url: (RootUrl + '/get_ble'),
        }).then((response) => {
          if (response.data.state.code == 2000) {
            let data = response.data.data
            that.isScaning = data.enable == '1' ? true : false
//            that.scanTime = data.scantime
//            that.alwaysScan = data.scanalways == '1' ? true : false
            that.rssi = data.fltrssi
            that.mac = data.fltnamemac
            that.cacheTime = data.cachetime
            that.row_data = data['Raw Data'] == '1' ? true : false
            that.iBeacon = data['iBeacon'] == '1' ? true : false
            that.MkiBeacon = data['MkiBeacon'] == '1' ? true : false
            that.MkiBeacon3Axis = data['MkiBeacon&3Axis'] == '1' ? true : false
            that.MkBeaconX3Axis = data['MkBeaconX-3Axis'] == '1' ? true : false
            that.MkBeaconXHT = data['MkBeaconX-H&T'] == '1' ? true : false
            that.EddystoneUID = data['Eddystone-UID'] == '1' ? true : false
            that.EddystoneTLM = data['Eddystone-TLM'] == '1' ? true : false
            that.EddystoneURL = data['Eddystone-URL'] == '1' ? true : false
          }
        })
        console.log("isScaning"+that.isScaning)
      },
      submitForm: function () {
        var that = this
        if(this.isScaning){
          if(!this.cacheTime){
            alert('All fields marked with * are required.')
            return
          }
          if(this.cacheTimeError || this.rssiError){
            return
          }
        }
        if (this.newPassword && !this.newPasswordError && this.confirmPassword === '') {
          this.confirmPasswordError = true
        }
        if (this.newPasswordError || this.confirmPasswordError) {
          return
        }
        request({
          method: 'post',
          url: (RootUrl + '/set_ble'),
          data: {
            enable: this.isScaning ? 1 : 0,
//            scantime: this.scanTime,
//            scanalways: this.alwaysScan ? 1 : 0,
            fltrssi: this.rssi,
            fltnamemac: this.mac,
            cachetime: this.cacheTime,
            'Raw Data': this.row_data ? 1 : 0,
            'iBeacon': this.iBeacon ? 1 : 0,
            'MkiBeacon': this.MkiBeacon ? 1 : 0,
            'MkiBeacon&3Axis': this.MkiBeacon3Axis ? 1 : 0,
            'MkBeaconX-3Axis': this.MkBeaconX3Axis ? 1 : 0,
            'MkBeaconX-H&T': this.MkBeaconXHT ? 1 : 0,
            'Eddystone-UID': this.EddystoneUID ? 1 : 0,
            'Eddystone-TLM': this.EddystoneTLM ? 1 : 0,
            'Eddystone-URL': this.EddystoneURL ? 1 : 0,
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
