var config = require('../../config')
var util = require('../../utils/util.js')
// pages/device/device.js
Page({
  

  /**
   * 组件的初始数据
   */
  data: {
    card_id : '',
    number: '',
    totalToday: '',
    total: '',
    offset : 0,
    totalUserNum: 0
  },

  onLoad : function (options){
    this.setData({card_id: options.card_id, number: options.number})
    var self = this
    var options = {
      url: config.service.dataUrl,
      data: {
        type: 6,
        card_id: self.data.card_id,
        offset: 0,
      },
      header: {
        'content-type': 'application/json'
      },
      success: function (res) {
        console.log(res)
        if (res.data)
          self.setData({ listData: res.data.records, totalToday : res.data.totalToday, total : res.data.total, totalUserNum : res.data.totalUserNum })
      },

      fail: function (e) {
        console.log("Fail")
      }
    }
    wx.request(options)
  },

  pullUpLoad : function () {
    console.log("pullUp")
    var self = this
    self.data.offset += 10
    var options = {
      url: config.service.dataUrl,
      data: {
        type: 6,
        card_id: self.data.card_id,
        offset: self.data.offset,
      },
      header: {
        'content-type': 'application/json'
      },
      success: function (res) {
        console.log(res)
        if (res.data){
          var temp = self.data.listData.concat(res.data.records)
          self.setData({ listData: temp, totalToday: res.data.totalToday, total: res.data.total })
          util.showSuccess("加载数据成功")
        }
      },

      fail: function (e) {
        console.log("Fail")
      }
    }
    wx.request(options)
  },
  onPullDownRefresh: function () {
    this.pullUpLoad()
    wx.stopPullDownRefresh()
  }
})
