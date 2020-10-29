<template>
  <div id="wifi-setting-content" class="status-content-wrapper">
    <!-- Content Header (Page header) -->
    <section class="content-header">
      <ol class="breadcrumb">
        <li>
          <v-icon name="SystemSetting"></v-icon>
          SYSTEM
        </li>
        <li class="active">Backup&Upgrade</li>
      </ol>
    </section>

    <section class="content">
      <div class="content-title">Backup</div>
      <div class="content-form">
        <div class="row">
          <span class="col-md-3 text-right"><b>Download Backup:</b></span>
          <div class="col-md-9">
            <button class="btn btn-primary" @click="getBackUp()">Generate Archive</button>
            <a style="display: none" id="getBackUp" :href="backUpUrl" download></a>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Restore Backup:</b></span>
          <div class="col-md-9">
            <input type="file" ref="restoreBackupFile" style="margin-top: 7px;"
                   @change="handleFileUpload('restoreBackupFile')"/>
            <button class="btn btn-primary" @click="restoreBackup()">Upload Archive</button>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Reset To Defaults:</b></span>
          <div class="col-md-9">
            <button class="btn btn-primary" @click="resetToDefault()">Perform</button>
          </div>
        </div>
      </div>
      <div class="content-title">Upgrade</div>
      <div class="content-form">
        <div class="row">
          <span class="col-md-3 text-right"><b>Current Firmware Version:</b></span>
          <div class="col-md-9">
            <span>{{ SystemVersion }}</span>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Whether To Save The Configuration:</b></span>
          <div class="col-md-9">
            <input type="checkbox" v-model="savecfg" style="width: 13px;zoom: 180%;margin-left: 8px;"/>
          </div>
        </div>
        <div class="row">
          <span class="col-md-3 text-right"><b>Upgrade File:</b></span>
          <div class="col-md-9">
            <input type="file" ref="uploadArchiveFile" style="margin-top: 7px;"
                   @change="handleFileUpload('uploadArchiveFile')"/>
            <button class="btn btn-primary" @click="updateSystem()">Upgrade</button>
          </div>
        </div>
      </div>
    </section>
    <div class="modal fade" id="alertModal" data-toggle="modal">
      <div class="modal-dialog" role="document">
        <div class="modal-content">
          <div class="modal-body">
            <p>{{ uploadType == 'upgrade' ? 'Please upload an upgrade file!' : 'Please choose a backup file!' }}</p>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-primary" data-dismiss="modal">ok</button>
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
  import {RootUrl, RootSetUrl} from '../public.js'
  import {request} from '../axios'

  export default {
    name: 'backup_upgrade',
    components: {
      'need_reboot_modal': NeedRebootModal,
    },
    data() {
      return {
        SystemVersion: '',
        backUpUrl: '',
        restoreBackupFile: '',
        uploadArchiveFile: '',
        savecfg: '',
        uploadType: ''
      }
    },
    mounted: function () {
      this.init_data()
    },
    methods: {
      handleFileUpload: function (fileName) {
        this.$data[fileName] = this.$refs[fileName].files[0];
      },
      init_data: function () {
        var that = this
        request({
          method: 'get',
          url: (RootUrl + '/sysstatus'),
        }).then((response) => {
          if (response.data.state.code == 2000) {
            let data = response.data.data
            that.SystemVersion = data.deviceinfo.sysversion
          }
        })
      },
      getBackUp: function () {
        var that = this
        request({
          method: 'get',
          url: (RootUrl + '/get_sysconf'),
        }).then((response) => {
          if (response.data.state.code == 2000) {
            let data = response.data.data
            that.backUpUrl = window.location.origin + '/' + data.url
            that.$nextTick(function () {
              document.getElementById('getBackUp').click()
            })
          }
        })
      },
      restoreBackup: function () {
        let formData = new FormData();
        if(!this.restoreBackupFile){
          this.uploadType = 'backup'
          $("#alertModal").modal('show')
          return
        }
        formData.append('restoreBackupFile', this.restoreBackupFile);
        request({
          method: 'post',
          url: (RootSetUrl + '/upload_settings.cgi'),
          data: formData,
          headers: {'Content-Type': 'multipart/form-data'}
        }).then((response) => {
          if (response.data.state.code == 2000) {
            $("#needRebootModal").modal('show');
          }
        })
      },
      resetToDefault: function () {
        if(confirm("Are you sure to reset the gateway to defaults?")){
          request({
            method: 'get',
            url: (RootUrl + '/sys_reset'),
          }).then((response) => {
            if (response.data.state.code == 2000) {
              ("#needRebootModal").modal('show');
            }
          })
        }
      },
      updateSystem: function () {
        let formData = new FormData();
        if(!this.uploadArchiveFile){
          this.uploadType = 'upgrade'
          $("#alertModal").modal('show')
          return
        }
        formData.append('uploadArchiveFile', this.uploadArchiveFile);
        formData.append('savecfg', this.savecfg ? 1 : 0);
        request({
          method: 'post',
          url: (RootSetUrl + '/upload.cgi'),
          data: formData,
          headers: {'Content-Type': 'multipart/form-data'}
        }).then((response) => {
          if (response.data.state.code == 2000) {
            $("#needRebootModal").modal('show');
          }
        })
      }
    }
  }
</script>
