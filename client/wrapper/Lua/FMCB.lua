arr = {2, 5, 6}

function printAll()
     for i = 1, 3 do
          print(arr[i])
     end
end

test = require("libFMCBLua")
print(test.int_cube(3))
printAll()