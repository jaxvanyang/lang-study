Get-ChildItem * -Include *.tmp -Recurse | Remove-Item
Get-ChildItem * -Include *.exe -Recurse | Remove-Item
Get-ChildItem * -Include *.class -Recurse | Remove-Item
Get-ChildItem * -Include *.txt -Recurse | Remove-Item
Get-ChildItem * -Include *.out -Recurse | Remove-Item
Get-ChildItem * -Include __pycache__ -Recurse | Remove-Item -Recurse
