Pod::Spec.new do |s|
  s.name         = "DSNetwork"
  s.version      = "0.2.0"
  s.summary      = "DSNetwork is a network library"
  s.authors      = {"ORCHAN"=>"1018563248@qq.com"}
  s.license      = {:type => "MIT", :file => "LICENSE"}
  s.homepage     = "https://github.com/orchan/DSNetwork"
  
  s.platform     = :ios
  s.swift_version = '4.0'
  s.ios.deployment_target = "8.0"
  
  s.requires_arc = true
  s.frameworks   = "UIKit"
  s.vendored_framework = 'DSNetwork.framework'

  s.dependency 'AFNetworking', '~> 3.2'
  s.source = { :git => "https://github.com/orchan/DSNetwork.git", :tag => s.version.to_s}
end
