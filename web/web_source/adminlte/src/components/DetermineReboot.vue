<template>
  <div class="modal fade" id="determineRebootModal" data-toggle="modal">
    <div class="modal-dialog" role="document">
      <div class="modal-content">
        <div class="modal-body">
          <p>Please restart the gateway to make the configuration take effect. Restart immediately?</p>
        </div>
        <div class="modal-footer">
          <button type="button" class="btn btn-default" data-dismiss="modal">CANCEL</button>
          <button type="button" class="btn btn-primary" @click="restart()">RESTART</button>
        </div>
      </div>
    </div>
  </div>
</template>
<script>
  import {mapMutations} from 'vuex'
  import {RootUrl} from '../public.js'
  import axios from 'axios'

  export default {
    name: 'determine_reboot_modal',
    methods: {
      ...mapMutations([
        'signOut'
      ]),
      restart: function () {
        this.$emit('restart')
      }
    }
  }

</script>
