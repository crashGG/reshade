Param(
	[Parameter(Mandatory = $true)][string]
	$path,
	[string]
	$config = "Release",
	[string]
	$platform = "x64"
)

$exists = Test-Path $path
$version = 0,0,0,0

# Get version from existing file
if ($exists -and $(Get-Content $path | Out-String) -match "VERSION_FULL (\d+).(\d+).(\d+).(\d+)") {
	$version = [int]::Parse($matches[1]), [int]::Parse($matches[2]), [int]::Parse($matches[3]), [int]::Parse($matches[4])
}
elseif ($(git describe --tags) -match "v(\d+)\.(\d+)\.(\d+)(-\d+-\w+)?") {
	$version = [int]::Parse($matches[1]), [int]::Parse($matches[2]), [int]::Parse($matches[3]), 0
}

# Increment build version for release builds
if (($config -eq "Release") -or
    ($config -eq "Release Signed")) {
	$version[3] += 1
	"Updating version to $([string]::Join('.', $version)) ..."
}
elseif ($exists) {
	return
}

$official = Test-Path ($path + "\..\sign.pfx")

# Update version file with the new version information
@"
#pragma once

#define VERSION_FULL 6.4.9.9
#define VERSION_MAJOR 6
#define VERSION_MINOR 4
#define VERSION_REVISION 9
#define VERSION_BUILD 9

#define VERSION_STRING_FILE "6.4.9.9"
#define VERSION_STRING_PRODUCT "6.4.X DEV"
"@ | Out-File -FilePath $path -Encoding ASCII
