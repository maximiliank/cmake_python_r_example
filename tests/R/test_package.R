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

test_that("vec_add", {
    res <- RCppLib::vec_add(c(1, 2, 3), c(4, 5, 6))
    expect_identical(res, c(5, 7, 9))
})

test_that("vec_square_inplace", {
    x <- c(4, 5, 6)
    RCppLib::vec_square_inplace(x)
    expect_identical(x, c(16, 25, 36))
})
