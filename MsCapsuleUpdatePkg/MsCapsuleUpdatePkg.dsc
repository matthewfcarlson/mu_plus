##
# Copyright (c) 2016, Microsoft Corporation

# All rights reserved.
# Redistribution and use in source and binary forms, with or without 
# modification, are permitted provided that the following conditions are met:
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##


[Defines]
  PLATFORM_NAME                  = MsCapsuleUpdatePkg
  PLATFORM_GUID                  = 72E3CFC6-6E7D-44EC-8056-6D2175F1997C
  PLATFORM_VERSION               = 0.96
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/MsCapsuleUpdatePkg
  SUPPORTED_ARCHITECTURES        = IA32|X64
  BUILD_TARGETS                  = DEBUG|RELEASE|NOOPT
  SKUID_IDENTIFIER               = DEFAULT

[LibraryClasses]
  #
  # Entry point
  #
  PeiCoreEntryPoint|MdePkg/Library/PeiCoreEntryPoint/PeiCoreEntryPoint.inf
  PeimEntryPoint|MdePkg/Library/PeimEntryPoint/PeimEntryPoint.inf
  DxeCoreEntryPoint|MdePkg/Library/DxeCoreEntryPoint/DxeCoreEntryPoint.inf
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf

  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf 
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf 
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  UefiBootManagerLib|MdeModulePkg/Library/UefiBootManagerLib/UefiBootManagerLib.inf
  DxeServicesTableLib|MdePkg/Library/DxeServicesTableLib/DxeServicesTableLib.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
  OpensslLib|CryptoPkg/Library/OpensslLib/OpensslLib.inf
  IntrinsicLib|CryptoPkg/Library/IntrinsicLib/IntrinsicLib.inf
  BaseCryptLib|CryptoPkg/Library/BaseCryptLib/BaseCryptLib.inf
  FmpAuthenticationLib|SecurityPkg/Library/FmpAuthenticationLibPkcs7/FmpAuthenticationLibPkcs7.inf

  CapsuleUpdatePolicyLib|MsCapsuleUpdatePkg/Library/CapsuleUpdatePolicyLibNull/CapsuleUpdatePolicyLibNull.inf
  MsFmpPayloadHeaderLib|MsCapsuleUpdatePkg/Library/MsFmpPayloadHeaderV1DxeLib/MsFmpPayloadHeaderV1DxeLib.inf
  BmpSupportLib|MsCapsuleUpdatePkg/Library/BaseBmpSupportLib/BaseBmpSupportLib.inf
  SafeIntLib|MdePkg/Library/BaseSafeIntLib/BaseSafeIntLib.inf
  CapsulePersistLib|MsCapsuleUpdatePkg/Library/CapsulePersistLibNull/CapsulePersistLibNull.inf
  FmpHelperLib|MsCapsuleUpdatePkg/Library/FmpHelperLib/FmpHelperDxeLib.inf
  FmpPolicyLib|MsCapsuleUpdatePkg/Library/FmpPolicyLib/FmpPolicyDxeLib.inf
  CapsuleResetLib|MsCorePkg/Library/CapsuleResetLibNull/CapsuleResetLibNull.inf ##MSCHANGE

##MSCHANGE Begin
!if $(TARGET) == DEBUG
  #if debug is enabled provide StackCookie support lib so that we can link to /GS exports
  RngLib|MdePkg/Library/BaseRngLib/BaseRngLib.inf
  NULL|MdePkg/Library/BaseBinSecurityLibRng/BaseBinSecurityLibRng.inf
!endif
##MSCHANGE End

[LibraryClasses.X64]
  #
  # DXE phase common
  #
  PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf


[PcdsFeatureFlag]
#  <SET FEATURE PCDs FLAGS FOR THIS BUILD HERE>


[PcdsFixedAtBuild]
#  <SET FIXED AT BUILD PCDs FOR THIS BUILD HERE>


###################################################################################################
#
# Components Section - list of the modules and components that will be processed by compilation
#                      tools and the EDK II tools to generate PE32/PE32+/Coff image files.
#
# Note: The EDK II DSC file is not used to specify how compiled binary images get placed
#       into firmware volume images. This section is just a list of modules to compile from
#       source into UEFI-compliant binaries.
#       It is the FDF file that contains information on combining binary files into firmware
#       volume images, whose concept is beyond UEFI and is described in PI specification.
#       Binary modules do not need to be listed in this section, as they should be
#       specified in the FDF file. For example: Shell binary (Shell_Full.efi), FAT binary (Fat.efi),
#       Logo (Logo.bmp), and etc.
#       There may also be modules listed in this section that are not required in the FDF file,
#       When a module listed here is excluded from FDF file, then UEFI-compliant binary will be
#       generated for it, but the binary will not be put into any firmware volume.
#
###################################################################################################

[Components]
  MsCapsuleUpdatePkg\Library\BaseBmpSupportLib\BaseBmpSupportLib.inf
  MsCapsuleUpdatePkg\Library\CapsuleKeyBaseLibNull\CapsuleKeyBaseLibNull.inf
  MsCapsuleUpdatePkg\Library\CapsulePersistLibNull\CapsulePersistLibNull.inf
  MsCapsuleUpdatePkg\Library\FmpHelperLib\FmpHelperDxeLib.inf
  MsCapsuleUpdatePkg\Library\CapsuleUpdatePolicyLibNull\CapsuleUpdatePolicyLibNull.inf
  MsCapsuleUpdatePkg\Library\MsFmpPayloadHeaderV1DxeLib\MsFmpPayloadHeaderV1DxeLib.inf
  MsCapsuleUpdatePkg\Library\FmpWrapperDeviceLib\FmpWrapperDeviceLib.inf
  MsCapsuleUpdatePkg\Library\FmpPolicyLib\FmpPolicyDxeLib.inf

  MsCapsuleUpdatePkg\Universal\EsrtDxe\EfiSystemResourceTableDxe.inf

[BuildOptions]
  #Turn off optimization to ease in debugging. 
  DEBUG_VS2015x86_*_CC_FLAGS     = /Od

