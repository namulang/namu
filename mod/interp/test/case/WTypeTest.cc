#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {

    class Food : public Obj {
        WRD_CLASS(Food, Obj)

    public:
        Food(string newName, int newCalorie): name(newName), calorie(newCalorie) {}

        string name;
        int calorie;
    };

    class Chef : public Obj {

        class MyType : public WType {
            WRD_DECL_THIS(MyType, WType);

        protected:
            const Ases& _getImplis() const override {
                static Ases* inner = nullptr;
                if(inner) return *inner;

                inner = new Ases();
                struct ToFood : public As {
                    const WType& getType() const override {
                        return TType<Food>::get();
                    }
                    Ref as(const Node& obj) const override {
                        const Chef& chef = obj.cast<Chef>();
                        if(nul(chef)) return Ref();

                        return Ref(new Food(chef.foodName, chef.foodCalorie));
                    }
                };
                inner->push_back(new ToFood());

                return *inner;
            }
        };
        WRD_CLASS(Chef, Obj, MyType)

    public:
        string foodName;
        int foodCalorie;
    };
}

TEST(WTypeFixture, testChefImplicitCastToFood) {
    // prepare:
    const string expectName = "HealthPotion";
    const int expectCalorie = 350;
    Chef chef;
    chef.foodName = expectName;
    chef.foodCalorie = expectCalorie;

    const WType& chefType = chef.getType();
    ASSERT_TRUE(chefType.isImpli<Food>());
    TRef<Food> cast = chef.asImpli<Food>();
    ASSERT_TRUE(cast);

    EXPECT_EQ(cast->name, expectName);
    EXPECT_EQ(cast->calorie, expectCalorie);
}

