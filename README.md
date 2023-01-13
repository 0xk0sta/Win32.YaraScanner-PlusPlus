# Win32.YaraScanner-PlusPlus [WIP]
## Warning:
* The currently embedded yara ruleset is really bad, it will give a ton of false positives, this is intentional for testing purpouses. *
* To change the ruleset you just need to replace the file 'data1.bin' with your actual ruleset *

### TODO:
 - Accept embedded encrypted ruleset ( Probably initially RC4 encoding its key using a custom algorithm I've developed (Not yet public) )
 - Add splunk forwarding capabilities
 - Add really basic remediation capabilities based on the rule metadata (for example, a rule is critical = we terminate the process)
 - Optimize the program [Reduce CPU usage]
 
 # Images
![](https://github.com/0xk0sta/Win32.YaraScanner-PlusPlus/blob/main/Img/Sample.png)
