library(RCppLib)

test_that("MyClass1", {
    mc <- RCppLib::MyClass$new(3)
    expect_identical(mc$Area(), 9)
})

test_that("MyClass2", {
    mc <- RCppLib::MyClass$new(3, 4)
    expect_identical(mc$Area(), 12)
})

test_that("myfunction", {
    res <- RCppLib::myfunction(3, 4)
    expect_identical(res, 12)
})
