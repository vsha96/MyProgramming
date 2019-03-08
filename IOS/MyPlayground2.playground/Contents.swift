//: Playground - noun: a place where people can play
//-------------------------------------------------------
let x: Int = 5
var y: Double = 6

x + Int(y)

var a = 2, b = 14
b - a
b + a
b / a
b * a
a % b

//напечатать
print("значение = \(a)")

var str: String = "123"

print("значение в стринг \(str)" )

//значение стринг
Int(str)! + a
Int(str)

var i: Int = Int(str)!

// massive
var m = [1,2,3,4,7]
var array: [String] = []
var anotherarray = [String]()

m.capacity

array.append("first")
array.append("second")
m.removeLast(2)
m.count
m.capacity

// цикл for
for string in array {
    print(string)
}

//-------------------------------------------------------

import Foundation

str = "Hello, playground"

var num: [Int] = [1,2,3,4,5,6,7]
num.count

func isEven(n: Int) -> Bool {
    return n % 2 == 0
}
func isOdd(n: Int) -> Bool {
    return n % 2 != 0
}

func filter(arr: [Int], check: (Int) -> Bool) -> [Int] {
    var result: [Int] = []
    for n in arr {
        if check(n) {
            result.append(n)
        }
    }
    return result
}

filter(arr: num, check: isEven)
filter(arr: num, check: isOdd)

// классы ( в них засовываются методы (функции классов))

class Recipe: NSObject {
    var name: String
    static var x: Int?
    private(set) var ingredients: [String] = []
    init(name: String) {
        self.name = name
    }
    func addIngredient(item: String, count: Int) {
        self.ingredients.append("\(item)x\(count)")
    }
    func getIngredients() -> [String] {
        return self.ingredients
    }
    
}


var recipe = Recipe(name: "Оливье")
recipe.addIngredient(item: "Картофан", count: 5)
recipe.getIngredients()

recipe.name
Recipe.x

//опциональный
var optionalString: String?
print(optionalString)

//protocols

protocol Vehicle {
    var wheels: Int {get set}
    var requiresFuel: Bool { get }
    
    func start() -> String
}





