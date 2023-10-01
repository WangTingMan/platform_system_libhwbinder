#include <hwbinder/hidl_parcel_writer_impl.h>

namespace android
{

    status_t hidl_parcel_writer_impl::no_impl()const
    {
        return -1;
    }

    void register_detail_hidl_parcel_writer()
    {
        parcel_writer_maker maker;
        maker = []()
            {
                return std::make_shared<hidl_parcel_writer_impl>();
            };

        register_hidl_parcel_writer_maker( maker );
    }

    void hidl_parcel_writer_impl::copy_to( uint8_t* a_dest, uint32_t a_size )
    {
        memcpy( a_dest, m_detail.data(), a_size );
    }

    uint32_t hidl_parcel_writer_impl::size()
    {
        return m_detail.dataSize();
    }


}
