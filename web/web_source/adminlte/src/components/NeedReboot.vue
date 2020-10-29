<template>
  <div class="rebootModal">
    <div class="modal fade" id="needRebootModal" data-toggle="modal" data-backdrop="static">
      <div class="modal-dialog" role="document">
        <div class="modal-content">
          <div class="modal-body">
            <p>The gateway will restart. Please reconnect to the gateway.</p>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-primary" @click="rebootAndLogOut()">ok</button>
          </div>
        </div>
      </div>
    </div>
    <div class="modal fade" id="loadingModal" data-toggle="modal" data-backdrop="static">
      <div style="margin: auto;display: block;position: relative;top: 50%;margin-top: -140px; width: 328px;">
        <img src="../assets/img/loading.gif">
        <p class="text-center" style="position: absolute;width: 328px;bottom: 40px;color: #fff;font-size: 20px;">Loading…</p>
      </div>
    </div>
  </div>
</template>
<script>
  import {mapMutations} from 'vuex'
  import {request} from '../axios'
  import {RootUrl} from '../public.js'

  export default {
    name: 'need_reboot_modal',
    methods: {
      ...mapMutations([
        'signOut'
      ]),
      rebootAndLogOut: function () {
        $("#needRebootModal").modal('hide')
        $("#loadingModal").modal('show')
        request({
          method: 'get',
          url: (RootUrl + '/logout'),
          timeout: 3000
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
