function Component()
{
  Component.prototype.createOperations = function()
  {
    // call default implementation
    component.createOperations();

    // ... add custom operations

    var kernel = systemInfo.kernelType;
    if( kernel != "winnt" ) {
      var exePath = installer.value("TargetDir") + "/bin/openstudio";
      component.addElevatedOperation("CreateLink", "/usr/local/bin/openstudio", exePath );
    }
  }
}


