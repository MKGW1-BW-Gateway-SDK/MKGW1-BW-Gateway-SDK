<template>
  <aside id="slider" class="main-sidebar">
    <!-- sidebar: style can be found in sidebar.less -->
    <section class="sidebar">
      <!-- sidebar menu: : style can be found in sidebar.less -->
      <ul data-widget="tree" class="sidebar-menu">
        <va-slide-item
          v-for="(item,index) in slideMenuItems"
          :data="item"
          :key="index"
          :type="item.type"
          :isHeader="item.isHeader"
          :icon="item.icon"
          :name="item.name"
          :badge="item.badge"
          :items="item.items"
          :router="item.router"
          :link="item.link"
        >
        </va-slide-item>
      </ul>
    </section>
    <footer>
      <p>MOKO TECHNOLOGY LTD.</p>
      <a href="http://www.mokosmart.com">www.mokosmart.com</a>
    </footer>
    <!-- /.sidebar -->
  </aside>
</template>

<script>
import VASlideItem from 'va/components/VASlideItem.vue'

export default {
  name: 'va-slider',
  props: {
    slideMenuItems: {
      type: Array,
      default: function(){
        return []
      }
    }
  },
  created () {

  },
  components: {
    'va-slide-item': VASlideItem
  }
}
</script>
