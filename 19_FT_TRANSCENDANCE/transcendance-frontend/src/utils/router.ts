/**
 * Router utils
 * @author Rony Gédéon
 * @version 1.0
 * @lastModif 2023-11-16
 */

import { Router } from 'vue-router'

/**
 * @name: pushToUserProfile
 * @description: Push to user profile page
 * @param {number} userId - User id
 * @return {void}
 */
export const pushToUserProfile = async (userId: number, router: Router) => {
  try {
    return await router.push({
      name: 'user-profile',
      params: {
        userId: userId,
        tab: 'profile'
      }
    })
  } catch (error) {
    // handle error here
  }
}

/**
 * @name: pushToUserProfile
 * @description: Push to user profile page
 * @param {number} userId - User id
 * @return {void}
 */
export const pushToDmWithUser = async (userId: number, router: Router) => {
  try {
    await router.push({ name: 'dm', params: { contactId: userId } })
  } catch (error) {}
}
