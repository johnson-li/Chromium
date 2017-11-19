Setup
===

1. Get the chromium source code.
	
  - Follow the instruction on https://www.chromium.org/developers/how-tos/get-the-code, stop at the step `gn gen out/Default`
  - You will download the chromium source code to `/path/to/workspace/src`

2. Add this git repo
  
  - `git remote add github https://github.com/johnson-li/chromium.git`
  - `git fetch github huawei`
  - `git checkout huawei`

3. Compile the code

  - `gn args out/Default`, add `treat_warnings_as_errors = false` to the end of the file, save it and exit
  - Follow the instruction on https://www.chromium.org/quic/playing-with-quic

4. Update the code

  - If you update the code and it fails to compile, please follow the following steps
  - `git checkout master`
  - `gclient sync`
  - `git checkout huawei`
  - Then follow step 3 to compile the code