# Inherit device configuration for mocha.
$(call inherit-product, device/xiaomi/mocha/full_mocha.mk)

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_tablet_wifionly.mk)

# Device identifier. This must come after all inclusions
PRODUCT_DEVICE := mocha
PRODUCT_NAME := lineage_mocha
PRODUCT_BRAND := Xiaomi
PRODUCT_MODEL := Mi Pad
PRODUCT_MANUFACTURER := Xiaomi
