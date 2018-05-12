// pages/data/statistic.js
var config = require('../../config')

Page({

  /**
   * 页面的初始数据
   */
  data: {
    logged : false,
    username : '',
    password : ''
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

  // Setting username
  usernameInput : function (e) {
    this.setData({username : e.detail.value})
  },

  // Setting password
  passwordInput : function (e) {
    this.setData({ password: e.detail.value })
  },

  doBackendLogin : function () {
    var self = this
    var options = {
      url: config.service.backLoginUrl,
      data: {
        name: this.data.username,
        password: this.data.password
      },
      header: {
        'content-type': 'application/json'
      },
      success: function (res) {
        if (res.data.result)
          self.setData({logged : true})
      },

      fail: function (e) {
        console.log("Fail")
      }
    }
    wx.request(options)
  }

})