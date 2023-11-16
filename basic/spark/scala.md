
 - local file

    val textFile = sc.textFile("d:\\altran.txt")
    scala> textFile.count() // Number of items in this RDD
    scala> textFile.first() // First item in this RDD