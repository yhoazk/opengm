
#include <stdlib.h>
#include <vector>
#include <set>
#include <functional>

#include <opengm/datastructures/marray/marray.hxx>
#include <opengm/graphicalmodel/graphicalmodel.hxx>
#include <opengm/unittests/test.hxx>
#include <opengm/operations/adder.hxx>
#include <opengm/operations/multiplier.hxx>

struct OperationTest
{
   void testAdder() {
      typedef double        T;
      typedef opengm::Adder OP;
      T a=5;
      T b=6;
      T c=2;
      T d=4;
      std::vector<size_t> shape(2,4);
      marray::Marray<T> A(shape.begin(),shape.end(),2);
      marray::Marray<T> B(shape.begin(),shape.end(),6);
      marray::Marray<T> C(shape.begin(),shape.end(),1);

      {d = OP::neutral<T>();   OPENGM_TEST(d==0);}
      {d=1;OP::neutral(d);     OPENGM_TEST(d==0);}
      {d = OP::ineutral<T>();  OPENGM_TEST(d==0);}
      {d=1;OP::ineutral(d);    OPENGM_TEST(d==0);}
      {d=b;OP::op(a,d);        OPENGM_TEST(a==5 && d==11);}
      {d=0;OP::op(a,b,d);      OPENGM_TEST(a==5 && b==6 && d==11);}
      {a=5;OP::op(a,A);        OPENGM_TEST(a==5 && A(0,0)==7 && A(3,3)==7);}
      {OP::op(A,C);            OPENGM_TEST(A(0,0)==7 && A(3,3)==7 && C(0,0)==8&& C(3,3)==8);}
      {OP::op(A,B,C);          OPENGM_TEST(C(0,0)==13 && C(3,3)==13);}
      {d=b;OP::iop(a,d);       OPENGM_TEST(a==5 && d==1);}
      {a=5;OP::iop(a,A);       OPENGM_TEST(a==5 && A(0,0)==2 && A(3,3)==2);}
      {d=0;OP::iop(a,b,d);     OPENGM_TEST(a==5 && b==6 && d==-1);}
      {OPENGM_TEST(!OP::hasbop());}
      {b=6;OP::hop(b,A);           OPENGM_TEST(A(0,0)==12 && A(3,3)==12);}
      {b=6;OP::hop(c,b);           OPENGM_TEST(c==2 && b==12);}
      {b=6;OP::hop(a,b,c);         OPENGM_TEST(a==5 && b==6 && c==30);}
      {b=4;a=2;OP::ihop(a,b);      OPENGM_TEST(a==2 && b==2);}
      {a=8,b=2;OP::ihop(a,b,c);    OPENGM_TEST(a==8 && b==2 && c==4);}
   };

   void testMultiplier() {
      typedef double             T;
      typedef opengm::Multiplier OP;
      T a=5;
      T b=6;
      T c=2;
      T d=4;

      {d = OP::neutral<T>();      OPENGM_TEST(d==1);}
      {OP::neutral(d);            OPENGM_TEST(d==1);}
      {d = OP::ineutral<T>();     OPENGM_TEST(d==1);}
      {OP::ineutral(d);           OPENGM_TEST(d==1);}
      {a=5;b=6;c=2;OP::op(a,b);   OPENGM_TEST(a==5 && b==30);}
      {a=5;b=6;c=2;OP::op(a,b,c); OPENGM_TEST(a==5 && b==6 &&c==30);}
      {a=3;b=6;c=2;OP::iop(a,b);  OPENGM_TEST(a==3 && b==2);}
      {a=6;b=2;c=2;OP::iop(a,b,c);OPENGM_TEST(a==6 && b==2 && c==3);}
      {OPENGM_TEST(!OP::hasbop());}
      //{OP::hop(a,b);}
      //{OP::hop(a,b,c);}
      //{OP::ihop(a,b);}
      //{OP::ihop(a,b,c);}
   };

   void run() {
      std::cout << "    - Test Adder ..."<<std::flush;
      testAdder();
      std::cout <<" OK!"<<std::endl;

      std::cout << "    - Test Multiplier ..."<<std::flush;
      testMultiplier();
      std::cout <<" OK!"<<std::endl;
   };

};

int main() {
   std::cout << "Test Operatation (Adder /Multiplier)  "<< std::endl;
   {
      OperationTest t;
      t.run();
   }
   std::cout << "done.." << std::endl;
   return 0;
}
