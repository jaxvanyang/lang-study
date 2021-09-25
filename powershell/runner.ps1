param (
	[string]$SourceFile
)

function Compile-SourceFile([string]$SourceFile, [string]$OutFile) {
	g++ $SourceFile -O2 -Wall -o $OutFile
	return $?
}

if (!(Test-Path $SourceFile)) {
	Write-Error "Error: $SourceFile not exists"
	return
}

$OutFile = $SourceFile -replace '.cpp', '.exe'
if ($OutFile -like '*.cc') {
	$OutFile = $OutFile -replace '.cc', '.exe'
}

if (!(Test-Path $OutFile)) {
	if (!$(Compile-SourceFile $SourceFile $OutFile)) {
		Write-Error 'Compile Error'
		return
	}
} else {
	$SourceTime = (Get-Item $SourceFile).LastWriteTime
	$OutTime = (Get-Item $OutFile).LastWriteTime

	if ($SourceTime -gt $OutTime) {
		if (!(Compile-SourceFile $SourceFile $OutFile)) {
			Write-Error 'Compile Error'
			return
		}
	}
}

if (Test-Path "data.in") {
	Get-Content data.in | & $OutFile
} else {
	& $OutFile
}