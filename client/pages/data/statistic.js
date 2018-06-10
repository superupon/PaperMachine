// pages/data/statistic.js
var config = require('../../config')
var util = require('../../utils/util.js')
Page({

  /**
   * 页面的初始数据
   */
  data: {
    logged : false,
    username : '',
    password : '',
    viewType : 0,
    offset : 0,
    listData : [],
    devices: [],
    device_card_id: '',
    device_number : '',
    device_address: '',
    prize_activate: false,
    prize_name : '',
    prize_rate : 0.0,
    prize_number : 0,
    lastDevice : false
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

  // Setting device card id
  deviceCardIdInput: function (e) {
    this.setData({ device_card_id : e.detail.value })
  },

  // Setting password
  deviceNumberInput: function (e) {
    this.setData({ device_number : e.detail.value })
  },

  // Event handler for handling user input device address
  deviceAddressInput: function (e) {
    this.setData({ device_address: e.detail.value })
  },



  deleteBlacklist : function (e) {
    var self = this
    console.log(e.target.id)
    var options = {
      url: config.service.dataUrl,
      data: {
        type: 5,
        id: e.target.id,
      },
      header: {
        'content-type': 'application/json'
      },
      success: function (res) {
        util.showSuccess("成功的删除黑名单用户")
      },

      fail: function (e) {
        console.log("Fail")
      }
    }
    wx.request(options)
    console.log(options)
  },

  blacklistView : function(e) {
    var self = this
    this.setData({ viewType : 2, offset : 0, listData : []})
    var options = {
      url: config.service.dataUrl,
      data: {
        type: this.data.viewType,
        offset: 0,
      },
      header: {
        'content-type': 'application/json'
      },
      success: function (res) {
        if (res.data.length)
          self.setData({ listData : res.data })
      },

      fail: function (e) {
        console.log("Fail")
      }
    }
    wx.request(options)
  },

  dataView : function() {
    var self = this
    this.setData({ viewType: 1, offset: 0, lastDevice : false})
    var options = {
      url: config.service.dataUrl,
      data: {
        type: this.data.viewType,
        offset: 0,
      },
      header: {
        'content-type': 'application/json'
      },
      success: function (res) {
        if (res.data.length)
          self.setData({ listData: res.data })
      },

      fail: function (e) {
        console.log("Fail")
      }
    }
    wx.request(options)
  },
  pullUpLoad: function () {
    var self = this
    var temp_offset = this.data.offset
    temp_offset += 10
    this.setData({ viewType: 1, offset: temp_offset })
    console.log(temp_offset)
    var options = {
      url: config.service.dataUrl,
      data: {
        type: this.data.viewType,
        offset: temp_offset,
      },
      header: {
        'content-type': 'application/json'
      },
      success: function (res) {
        if (res.data.length)
        {
          if (res.data.length < 10 )
          {
            self.setData({lastDevice : true})
          }   
          var temp = self.data.listData.concat(res.data)
          self.setData({ listData: temp})
          util.showSuccess("加载数据成功")
        }  
      },

      fail: function (e) {
        console.log("Fail")
      }
    }
    if (!self.data.lastDevice)
      wx.request(options)
    else
      util.showSuccess("已经到底了")
  },
  pullUpLoadBlacklist: function () {
    var self = this
    var temp_offset = this.data.offset
    temp_offset += 10
    this.setData({ viewType: 2, offset: temp_offset })
    console.log(temp_offset)
    var options = {
      url: config.service.dataUrl,
      data: {
        type: this.data.viewType,
        offset: temp_offset,
      },
      header: {
        'content-type': 'application/json'
      },
      success: function (res) {
        if (res.data.length) {
          if (res.data.length < 10) {
            self.setData({ lastDevice: true })
          }
          var temp = self.data.listData.concat(res.data)
          self.setData({ listData: temp })
          util.showSuccess("加载数据成功")
        }
      },

      fail: function (e) {
        console.log("Fail")
      }
    }
    if (!self.data.lastDevice)
      wx.request(options)
    else
      util.showSuccess("已经到底了")
  },
  addDeviceView : function () {
    this.setData({viewType:3, listData : []})
    this.getNewDevice()
  },

  changeDevice : function (e) {
    var found = this.data.listData.find(function(element){
      return element.card_id == e.target.id
    })
    this.setData({viewType:3, device_card_id : found.card_id, device_number : found.number})
    this.setData({listData : []})
    this.getNewDevice()
  },

  getNewDevice : function() {
    var self = this
    this.setData({ offset: 0 })
    var options = {
      url: config.service.dataUrl,
      data: {
        type: 4,
        offset: 0,
      },
      header: {
        'content-type': 'application/json'
      },
      success: function (res) {
        console.log(res)
        if (res.data.length)
          self.setData({ listData: res.data })
      },

      fail: function (e) {
        console.log("Fail")
      }
    }
    wx.request(options)
  },
  pasteToCardIdInput : function(e) {
    this.setData({device_card_id: e.target.id})
  },
  addNewDevice : function() {
    var self = this
    var options = {
      url: config.service.dataUrl,
      data: {
        type : 3,
        card_id : this.data.device_card_id,
        number: this.data.device_number,
        address: this.data.device_address
      },
      header: {
        'content-type': 'application/json'
      },
      success: function (res) {
        util.showSuccess("成功添加新设备")
      },

      fail: function (e) {
        console.log("Fail")
      }
    }
    if(this.data.device_card_id != '')
      wx.request(options)
    console.log(options)
  },

  deleteDevice : function(e) {
    var self = this
    var options = {
      url: config.service.dataUrl,
      data: {
        type: 7,
        card_id: this.data.device_card_id,
      },
      header: {
        'content-type': 'application/json'
      },
      success: function (res) {
        util.showSuccess("成功删除设备")
      },

      fail: function (e) {
        console.log("Fail")
      }
    }
    if (this.data.device_card_id != '' && this.data.device_card_id.length == 15)
      wx.request(options)
  },
  showDevice : function (e) {
    console.log(e.target.dataset.card_id)
    wx.navigateTo({
      url: '../device/device?device_card_id=1' //+ e.target.dataset.card_id,
    })
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
  },

  onPullDownRefresh : function () {
    this.pullUpLoad()
    wx.stopPullDownRefresh()
  }

})