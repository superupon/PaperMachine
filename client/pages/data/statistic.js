// pages/data/statistic.js
var config = require('../../config')

Page({

  /**
   * 页面的初始数据
   */
  data: {
    logged : false
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
  
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {
  
  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {
  
  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {
  
  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {
  
  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {
  
  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {
  
  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {
  
  },

  doBackendLogin : function () {
    var options = {
      url: config.service.backLoginUrl,
      data: {
        name: 'test',
        password: 'test'
      },
      header: {
        'content-type': 'application/json'
      },
      success: function (res) {
        console.log("Success")
      },

      fail: function (e) {
        console.log("Fail")
      }
    }
    wx.request(options)
    console.log('doBackendLogin')
    this.setData({
      logged: true})
  }

})