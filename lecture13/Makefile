BOOST=/mnt/eclipse/acg/users/delozier/boost_1_48_0/build

all: regex.cpp regex2.cpp type_traits.cpp
	g++ -o regex regex.cpp -L$BOOST/lib/ -lboost_regex -I$BOOST/include/
	g++ -o regex2 regex2.cpp -L$BOOST/lib/ -lboost_regex -I$BOOST/include/
	g++ -o type_traits type_traits.cpp -I$BOOST/include/
