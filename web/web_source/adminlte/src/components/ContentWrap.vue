<template>
  <!-- Content Wrapper. Contains page content -->
  <div id="content-wrap" class="content-wrapper">
    <!-- Content Header (Page header) -->
      <transition name="page" mode="out-in">
        <router-view></router-view>
      </transition>
    <!-- /.content -->
  </div>
  <!-- /.content-wrapper -->
</template>

<script>
export default {
  name: 'va-content-wrap',
  created () {

  }
}
</script>

<style>
.page-enter-active, .page-leave-active {
  transition: opacity 0.5s, transform 0.5s;
}
.page-enter, .page-leave-to {
  opacity: 0;
}
</style>
