//
// Created by a.kiryanenko on 2019-05-17.
//

#ifndef GRAPH_API_SIMULATOR_H
#define GRAPH_API_SIMULATOR_H


#include <map>
#include "../libspu/base_structure.h"

using namespace std;

namespace SPU
{

    class Simulator : public BaseStructure {
        map<key_t, value_t> *_data = nullptr;

    public:
        explicit Simulator(bool initialize=true);
        Simulator(Simulator &obj);
        ~Simulator() override;

        u32 get_power() override;

        status_t insert(key_t key, value_t value, flags_t flags = NO_FLAGS) override;
        status_t del(key_t key, flags_t flags = NO_FLAGS) override;
        pair_t search(key_t key, flags_t flags = P_FLAG) override;
        pair_t min(flags_t flags = P_FLAG) override;
        pair_t max(flags_t flags = P_FLAG) override;
        pair_t next(key_t key, flags_t flags = P_FLAG) override;
        pair_t prev(key_t key, flags_t flags = P_FLAG) override;
        pair_t nsm(key_t key, flags_t flags = P_FLAG) override;
        pair_t ngr(key_t key, flags_t flags = P_FLAG) override;

    protected:
        adds_rslt_t createStructure() override;
        dels_rslt_t deleteStructure() override;
    };

    /// Созданные структуры
    extern map<gsid_t, map<key_t, value_t>*> globalStructures;

    gsid_t getNextGsid();
}

#endif //GRAPH_API_SIMULATOR_H
