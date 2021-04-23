#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {

    class food : public obj {
        WRD_CLASS(food, obj)

    public:
        food(string newName, int newCalorie): name(newName), calorie(newCalorie) {}

        string name;
        int calorie;
    };

    class chef : public obj {

        class myType : public wtype {
            WRD_DECL_ME(myType, wtype);

        protected:
            const casts& _getImplis() const override {
                static casts* inner = nullptr;
                if(inner) return *inner;

                inner = new casts();
                struct tofood : public cast {
                    const wtype& getType() const override {
                        return ttype<food>::get();
                    }
                    wrd::ref as(const node& it) const override {
                        const chef& chef1 = it.cast<chef>();
                        if(nul(chef1)) return wrd::ref();

                        return wrd::ref(new food(chef1.foodName, chef1.foodCalorie));
                    }
                };
                inner->push_back(new tofood());

                return *inner;
            }
        };
        WRD_CLASS(chef, obj, myType)

    public:
        string foodName;
        int foodCalorie;
    };
}

TEST(wtypeTest, testchefImplicitCastTofood) {
    // prepare:
    const string expectName = "HealthPotion";
    const int expectCalorie = 350;
    chef chef;
    chef.foodName = expectName;
    chef.foodCalorie = expectCalorie;

    const wtype& chefType = chef.getType();
    ASSERT_TRUE(chefType.isImpli<food>());
    tref<food> cast = chef.asImpli<food>();
    ASSERT_TRUE(cast);

    EXPECT_EQ(cast->name, expectName);
    EXPECT_EQ(cast->calorie, expectCalorie);
}

