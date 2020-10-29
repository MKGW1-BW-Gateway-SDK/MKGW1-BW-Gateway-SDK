module.exports = {
  configureWebpack: {
    resolve: {
      alias: {
        'assets': '@/assets',
        'components': '@/components',
        'va': 'vue2-admin-lte/src',
      }
    }
  },
}